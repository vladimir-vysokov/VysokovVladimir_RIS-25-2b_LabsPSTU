#include "graphview.h"
#include <QPainter>
#include <QPolygonF>
#include <cmath>
#include <QWheelEvent>
#include <QFrame>

const qreal GraphView::VERTEX_RADIUS = 26.0;

// ─────────────────────────────────────────────────────────
//  Позиции вершин по умолчанию — ТОЧНО как на картинке
//  Холст 560×460
//  Вершина 1 → индекс 0  (низ по центру-право)
//  Вершина 2 → индекс 1  (верх по центру)
//  Вершина 3 → индекс 2  (середина справа)
//  Вершина 4 → индекс 3  (середина слева)
//  Вершина 5 → индекс 4  (верх справа)
//  Вершина 6 → индекс 5  (низ слева)
// ─────────────────────────────────────────────────────────
static const QPointF DEFAULT_POS[6] = {
    QPointF(340, 360),   // вершина 1
    QPointF(240,  60),   // вершина 2
    QPointF(370, 230),   // вершина 3
    QPointF(120, 200),   // вершина 4
    QPointF(460,  80),   // вершина 5
    QPointF( 80, 390),   // вершина 6
};

GraphView::GraphView(QWidget* parent) : QGraphicsView(parent) {
    scene_ = new QGraphicsScene(this);
    setScene(scene_);
    setRenderHint(QPainter::Antialiasing);
    setRenderHint(QPainter::TextAntialiasing);
    setDragMode(QGraphicsView::ScrollHandDrag);
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    setBackgroundBrush(QBrush(QColor("#eef2f6")));
    setFrameShape(QFrame::NoFrame);
    setStyleSheet("background: #eef2f6; border: 1px solid #d7dde5; border-radius: 8px;");
}

void GraphView::setGraph(const Graph* g) {
    graph_ = g;
    autoLayout();
    refresh();
}

void GraphView::autoLayout() {
    if (!graph_) return;
    int n = graph_->vertexCount();
    positions_.resize(n);
    if (n == 0) return;

    if (n == 6) {
        // Используем позиции из методички
        for (int i = 0; i < 6; i++)
            positions_[i] = DEFAULT_POS[i];
    } else {
        // Для произвольных графов — круговое расположение
        double cx = 280, cy = 240, r = 170;
        for (int i = 0; i < n; i++) {
            double angle = 2.0 * M_PI * i / n - M_PI / 2.0;
            positions_[i] = QPointF(cx + r * cos(angle), cy + r * sin(angle));
        }
    }
}

void GraphView::setVertexPos(int idx, QPointF p) {
    if (idx >= 0 && idx < (int)positions_.size())
        positions_[idx] = p;
}

void GraphView::refresh() {
    if (!graph_) return;
    int n = graph_->vertexCount();
    while ((int)positions_.size() < n)
        positions_.push_back(QPointF(280, 240));
    drawGraph();
}

// ─────────────────────────────────────────────────────────
//  РИСОВАНИЕ ГРАФА
// ─────────────────────────────────────────────────────────
void GraphView::drawGraph() {
    scene_->clear();
    if (!graph_) return;
    int n = graph_->vertexCount();

    // Обновляем сцену под размер
    scene_->setSceneRect(-30, -30, 620, 540);

    // 1. Сначала рисуем все рёбра
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (!graph_->hasEdge(i, j)) continue;

            // Подсветка пути
            bool onPath = false;
            for (int k = 0; k + 1 < (int)highlightedPath_.size(); k += 2)
                if (highlightedPath_[k] == i && highlightedPath_[k+1] == j)
                { onPath = true; break; }

            QColor edgeColor = onPath ? QColor("#d85c1f") : QColor("#64748b");
            int    edgeWidth = onPath ? 4 : 2;

            drawEdge(i, j, graph_->edgeWeight(i, j), edgeColor, edgeWidth);
        }
    }

    // 2. Рисуем вершины поверх рёбер
    for (int i = 0; i < n; i++) {
        QPointF p = positions_[i];

        bool isHighlighted = std::find(highlightedVertices_.begin(),
                                       highlightedVertices_.end(), i)
                             != highlightedVertices_.end();
        bool isOnPath = std::find(highlightedPath_.begin(),
                                  highlightedPath_.end(), i)
                        != highlightedPath_.end();

        QColor fill   = QColor("#ffffff");
        QColor border = QColor("#263545");
        int    bWidth = 2;

        if (isOnPath) {
            fill   = QColor("#ffe4c7");
            border = QColor("#d85c1f");
            bWidth = 3;
        } else if (isHighlighted) {
            fill   = QColor("#dbeafe");
            border = QColor("#1f6fb2");
            bWidth = 3;
        }

        auto* shadow = scene_->addEllipse(
            p.x() - VERTEX_RADIUS + 2, p.y() - VERTEX_RADIUS + 2,
            2*VERTEX_RADIUS, 2*VERTEX_RADIUS,
            QPen(Qt::NoPen), QBrush(QColor(39,49,63,35)));
        shadow->setZValue(1);

        auto* ell = scene_->addEllipse(
            p.x() - VERTEX_RADIUS, p.y() - VERTEX_RADIUS,
            2*VERTEX_RADIUS, 2*VERTEX_RADIUS,
            QPen(border, bWidth), QBrush(fill));
        ell->setZValue(2);

        // Номер вершины
        auto* txt = scene_->addText(
            QString::fromStdString(graph_->vertexName(i)));
        txt->setDefaultTextColor(QColor("#17202b"));
        txt->setFont(QFont("Arial", 12, QFont::Bold));
        QRectF tb = txt->boundingRect();
        txt->setPos(p.x() - tb.width()/2, p.y() - tb.height()/2);
        txt->setZValue(3);
    }
}

// ─────────────────────────────────────────────────────────
//  РИСОВАНИЕ РЕБРА С СТРЕЛКОЙ
// ─────────────────────────────────────────────────────────
void GraphView::drawEdge(int from, int to, int weight,
                         QColor color, int width) {
    QPointF pf = positions_[from];
    QPointF pt = positions_[to];

    QPointF dir = pt - pf;
    double len = std::sqrt(dir.x()*dir.x() + dir.y()*dir.y());
    if (len < 1e-6) return;
    dir /= len;
    QPointF perp(-dir.y(), dir.x());

    // Если есть обратное ребро — слегка смещаем оба
    bool hasReverse = graph_->hasEdge(to, from);
    double off = hasReverse ? 7.0 : 0.0;

    QPointF start = pf + dir * VERTEX_RADIUS + perp * off;
    QPointF end   = pt - dir * VERTEX_RADIUS + perp * off;

    // Линия ребра
    QPen pen(color, width);
    pen.setCapStyle(Qt::RoundCap);
    auto* line = scene_->addLine(QLineF(start, end), pen);
    line->setZValue(0);

    // Стрелка
    const double arrowLen   = 13.0;
    const double arrowAngle = M_PI / 6.5;  // угол раствора стрелки
    double angle = std::atan2(end.y() - start.y(), end.x() - start.x());

    QPointF tip = end;  // вершина стрелки
    QPointF ap1 = tip - QPointF(
        std::cos(angle - arrowAngle) * arrowLen,
        std::sin(angle - arrowAngle) * arrowLen);
    QPointF ap2 = tip - QPointF(
        std::cos(angle + arrowAngle) * arrowLen,
        std::sin(angle + arrowAngle) * arrowLen);

    QPolygonF arrow;
    arrow << tip << ap1 << ap2;
    scene_->addPolygon(arrow,
        QPen(color, 1),
        QBrush(color))->setZValue(1);

    // Подпись веса — сбоку от середины ребра
    QPointF mid = (start + end) / 2.0 + perp * (hasReverse ? 14.0 : 12.0);

    // Белый прямоугольник под цифрой (чтобы не сливалась с линиями)
    auto* wlbl = scene_->addText(QString::number(weight));
    wlbl->setDefaultTextColor(QColor("#17202b"));
    wlbl->setFont(QFont("Arial", 9, QFont::Bold));
    QRectF wb = wlbl->boundingRect();
    wlbl->setPos(mid.x() - wb.width()/2, mid.y() - wb.height()/2);
    wlbl->setZValue(2);

    // Подложка под цифрой
    auto* bg = scene_->addRect(
        mid.x() - wb.width()/2 - 1,
        mid.y() - wb.height()/2,
        wb.width() + 2, wb.height(),
        QPen(QColor("#d7dde5")), QBrush(QColor("#ffffff")));
    bg->setZValue(1);
    // Перерисовываем текст поверх подложки
    wlbl->setZValue(2);
}

// ─────────────────────────────────────────────────────────
//  ПОДСВЕТКА
// ─────────────────────────────────────────────────────────
void GraphView::highlightPath(const std::vector<int>& path) {
    highlightedPath_.clear();
    highlightedVertices_ = path;
    for (int i = 0; i + 1 < (int)path.size(); i++) {
        highlightedPath_.push_back(path[i]);
        highlightedPath_.push_back(path[i+1]);
    }
    drawGraph();
}

void GraphView::highlightVertices(const std::vector<int>& order) {
    highlightedVertices_ = order;
    highlightedPath_.clear();
    drawGraph();
}

void GraphView::clearHighlights() {
    highlightedVertices_.clear();
    highlightedPath_.clear();
    drawGraph();
}

// ─────────────────────────────────────────────────────────
//  МЫШЬ
// ─────────────────────────────────────────────────────────
void GraphView::mousePressEvent(QMouseEvent* e) {
    if (e->button() == Qt::LeftButton) {
        QPointF sp = mapToScene(e->pos());
        if (graph_) {
            for (int i = 0; i < graph_->vertexCount(); i++) {
                QPointF d = sp - positions_[i];
                if (d.x()*d.x() + d.y()*d.y() <=
                    VERTEX_RADIUS * VERTEX_RADIUS * 1.3) {
                    emit vertexClicked(i);
                    return;
                }
            }
        }
    }
    QGraphicsView::mousePressEvent(e);
}

void GraphView::wheelEvent(QWheelEvent* e) {
    if (!(e->modifiers() & (Qt::ControlModifier | Qt::MetaModifier))) {
        e->ignore();
        return;
    }

    double factor = e->angleDelta().y() > 0 ? 1.15 : 0.87;
    scale(factor, factor);
    e->accept();
}
