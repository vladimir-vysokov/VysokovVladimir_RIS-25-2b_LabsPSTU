#pragma once
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QGraphicsTextItem>
#include <QMouseEvent>
#include <QPointF>
#include <vector>
#include <functional>
#include "graph.h"

struct VertexItem {
    QGraphicsEllipseItem* circle = nullptr;
    QGraphicsTextItem* label = nullptr;
    QPointF pos;
};

struct EdgeItem {
    int from, to;
    QGraphicsLineItem* line = nullptr;
    QGraphicsPolygonItem* arrow = nullptr;
    QGraphicsTextItem* weightLabel = nullptr;
};

class GraphView : public QGraphicsView {
    Q_OBJECT
public:
    explicit GraphView(QWidget* parent = nullptr);
    void setGraph(const Graph* g);
    void refresh();

    // Highlight
    void highlightPath(const std::vector<int>& path);
    void highlightVertices(const std::vector<int>& order);
    void clearHighlights();

    // Layout
    void autoLayout();
    void setVertexPos(int idx, QPointF p);

signals:
    void vertexClicked(int idx);

protected:
    void mousePressEvent(QMouseEvent* e) override;
    void wheelEvent(QWheelEvent* e) override;

private:
    void drawGraph();
    void drawEdge(int from, int to, int weight, QColor color, int width);
    void drawArrow(QPointF from, QPointF to, QColor color, int width);
    QPointF edgePoint(int idx, QPointF toPos, qreal radius) const;

    const Graph* graph_ = nullptr;
    QGraphicsScene* scene_;
    std::vector<QPointF> positions_;
    std::vector<int> highlightedVertices_;
    std::vector<int> highlightedPath_; // pairs (from, to)

    static const qreal VERTEX_RADIUS;
};
