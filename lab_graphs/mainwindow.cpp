#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QGroupBox>
#include <QSplitter>
#include <QTextEdit>
#include <QTabWidget>
#include <QTableWidget>
#include <QHeaderView>
#include <QMessageBox>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QListWidget>
#include <QSpinBox>
#include <QFormLayout>
#include <QFrame>
#include <QSizePolicy>
#include <QScrollArea>

// ═══════════════════════════════════════════════════════
//  КОНСТРУКТОР
// ═══════════════════════════════════════════════════════
MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    setWindowTitle("Алгоритмы на графах - визуализатор");
    resize(1480, 900);

    setStyleSheet(R"(
        QMainWindow { background: #f3f5f7; }
        QWidget {
            background: #f3f5f7;
            color: #202733;
            font-family: 'Inter', 'SF Pro Text', 'Segoe UI', 'Arial';
            font-size: 13px;
        }

        QFrame#Header {
            background: #17202b;
            border: 0;
            border-radius: 8px;
        }
        QLabel#AppTitle {
            background: transparent;
            color: #ffffff;
            font-size: 20px;
            font-weight: 700;
        }
        QLabel#AppSubtitle {
            background: transparent;
            color: #aeb9c6;
        }
        QLabel#SectionTitle {
            color: #27313f;
            font-size: 15px;
            font-weight: 700;
            padding: 2px 0;
        }

        QGroupBox {
            background: #ffffff;
            border: 1px solid #d7dde5;
            border-radius: 8px;
            margin-top: 12px;
            padding: 12px 10px 10px 10px;
            font-weight: 700;
            color: #27313f;
        }
        QGroupBox::title {
            subcontrol-origin: margin;
            left: 12px;
            padding: 0 6px;
            background: #ffffff;
        }

        QPushButton {
            background: #ffffff;
            border: 1px solid #c7d0dc;
            border-radius: 6px;
            padding: 8px 12px;
            color: #253143;
            font-weight: 600;
        }
        QPushButton:hover { background: #eef4fb; border-color: #6c9fd6; }
        QPushButton:pressed { background: #dbeafe; }
        QPushButton#btnBFS, QPushButton#btnDFS, QPushButton#btnDijk, QPushButton#btnFloyd {
            color: #ffffff;
            border: 0;
            min-height: 38px;
        }
        QPushButton#btnBFS { background: #1f6fb2; }
        QPushButton#btnDFS { background: #2f8f63; }
        QPushButton#btnDijk { background: #8057b6; }
        QPushButton#btnFloyd { background: #c66a22; }
        QPushButton#Danger { background: #fff1f0; color: #b42318; border-color: #f0b8b2; }
        QPushButton#Success { background: #eaf7ef; color: #166534; border-color: #9ed8b4; }

        QComboBox, QSpinBox, QLineEdit {
            background: #ffffff;
            border: 1px solid #c7d0dc;
            border-radius: 6px;
            padding: 6px 8px;
            min-height: 22px;
            color: #202733;
        }
        QComboBox QAbstractItemView {
            background: #ffffff;
            color: #202733;
            selection-background-color: #dbeafe;
        }
        QTextEdit, QListWidget {
            background: #101820;
            border: 1px solid #263545;
            border-radius: 8px;
            color: #e7edf5;
            font-family: 'Menlo', 'Consolas', 'Courier New', monospace;
            font-size: 12px;
        }
        QListWidget::item { padding: 5px 7px; }
        QListWidget::item:hover { background: #1d2a38; }
        QListWidget::item:selected { background: #1f6fb2; color: #ffffff; }

        QTableWidget {
            background: #ffffff;
            border: 1px solid #d7dde5;
            border-radius: 8px;
            color: #202733;
            gridline-color: #d7dde5;
            selection-background-color: #dbeafe;
        }
        QHeaderView::section {
            background: #edf1f5;
            color: #4c5a6b;
            border: 1px solid #d7dde5;
            padding: 6px;
            font-weight: 700;
        }

        QTabWidget::pane { border: 0; }
        QTabBar::tab {
            background: #e6ebf1;
            color: #4c5a6b;
            border: 1px solid #d7dde5;
            padding: 8px 14px;
            margin-right: 4px;
            border-radius: 6px;
        }
        QTabBar::tab:selected {
            background: #17202b;
            color: #ffffff;
            border-color: #17202b;
            font-weight: 700;
        }
        QSplitter::handle { background: #d7dde5; width: 4px; }
        QLabel { color: #566579; }
        QScrollArea {
            background: #f3f5f7;
            border: 0;
        }
        QScrollBar:vertical {
            background: #edf1f5;
            width: 10px;
            margin: 0;
        }
        QScrollBar::handle:vertical {
            background: #aeb9c6;
            border-radius: 5px;
            min-height: 32px;
        }
        QScrollBar::add-line:vertical,
        QScrollBar::sub-line:vertical {
            height: 0;
        }
    )");

    setupUi();
    setupMenus();

    graph.loadDefaultGraph();
    graphView->setGraph(&graph);
    refreshMatrix();
    refreshVertexLists();

    // Приветственное сообщение
    outputLog->setPlainText(
        "Граф из лабораторной работы №2 загружен.\n\n"
        "Вершины: 1, 2, 3, 4, 5, 6\n"
        "Тип: ориентированный взвешенный граф\n\n"
        "Рёбра:\n"
        "  5 → 2 : 21\n"
        "  5 → 3 : 30\n"
        "  2 → 4 : 20\n"
        "  2 → 1 : 28\n"
        "  4 → 2 : 39\n"
        "  4 → 1 : 15\n"
        "  4 → 6 : 31\n"
        "  3 → 1 : 13\n"
        "  6 → 1 : 18\n\n"
        "Выберите алгоритм и нажмите кнопку.\n"
        "Начальная вершина по умолчанию: 5."
    );
}

// ═══════════════════════════════════════════════════════
//  ПОСТРОЕНИЕ ИНТЕРФЕЙСА
// ═══════════════════════════════════════════════════════
void MainWindow::setupUi() {
    auto* scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setCentralWidget(scrollArea);

    auto* central = new QWidget;
    central->setMinimumSize(1040, 880);
    scrollArea->setWidget(central);

    auto* mainLayout = new QVBoxLayout(central);
    mainLayout->setContentsMargins(14, 14, 14, 14);
    mainLayout->setSpacing(12);

    auto* header = new QFrame;
    header->setObjectName("Header");
    auto* headerLayout = new QHBoxLayout(header);
    headerLayout->setContentsMargins(18, 14, 18, 14);

    auto* titleBlock = new QWidget;
    titleBlock->setStyleSheet("background: transparent;");
    auto* titleLayout = new QVBoxLayout(titleBlock);
    titleLayout->setContentsMargins(0, 0, 0, 0);
    titleLayout->setSpacing(2);
    auto* title = new QLabel("Алгоритмы на графах");
    title->setObjectName("AppTitle");
    auto* subtitle = new QLabel("Обход в ширину, обход в глубину, алгоритм Дейкстры, алгоритм Флойда и редактируемый ориентированный взвешенный граф");
    subtitle->setObjectName("AppSubtitle");
    titleLayout->addWidget(title);
    titleLayout->addWidget(subtitle);
    headerLayout->addWidget(titleBlock, 1);

    auto* btnLoadTop = new QPushButton("Граф из задания");
    auto* btnClearTop = new QPushButton("Очистить");
    btnClearTop->setObjectName("Danger");
    headerLayout->addWidget(btnLoadTop);
    headerLayout->addWidget(btnClearTop);
    connect(btnLoadTop, &QPushButton::clicked, this, &MainWindow::onLoadDefault);
    connect(btnClearTop, &QPushButton::clicked, this, &MainWindow::onClearGraph);
    mainLayout->addWidget(header);

    auto* quickGroup = new QGroupBox("Запуск алгоритмов");
    auto* quickLayout = new QGridLayout(quickGroup);
    quickLayout->setHorizontalSpacing(10);
    quickLayout->setVerticalSpacing(8);

    startVertexCombo = new QComboBox;
    endVertexCombo = new QComboBox;
    quickLayout->addWidget(new QLabel("Старт:"), 0, 0);
    quickLayout->addWidget(startVertexCombo, 0, 1);
    quickLayout->addWidget(new QLabel("Финиш:"), 0, 2);
    quickLayout->addWidget(endVertexCombo, 0, 3);

    auto* btnBFS = new QPushButton("Обход в ширину");
    auto* btnDFS = new QPushButton("Обход в глубину");
    auto* btnDijk = new QPushButton("Алгоритм Дейкстры");
    auto* btnFloyd = new QPushButton("Алгоритм Флойда");
    btnBFS->setObjectName("btnBFS");
    btnDFS->setObjectName("btnDFS");
    btnDijk->setObjectName("btnDijk");
    btnFloyd->setObjectName("btnFloyd");
    for (auto* button : {btnBFS, btnDFS, btnDijk, btnFloyd}) {
        button->setMinimumHeight(42);
        button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    }

    quickLayout->addWidget(btnBFS, 1, 0);
    quickLayout->addWidget(btnDFS, 1, 1);
    quickLayout->addWidget(btnDijk, 1, 2);
    quickLayout->addWidget(btnFloyd, 1, 3);
    for (int col = 0; col < 4; ++col)
        quickLayout->setColumnStretch(col, 1);
    mainLayout->addWidget(quickGroup);

    connect(btnBFS, &QPushButton::clicked, this, &MainWindow::onBFS);
    connect(btnDFS, &QPushButton::clicked, this, &MainWindow::onDFS);
    connect(btnDijk, &QPushButton::clicked, this, &MainWindow::onDijkstra);
    connect(btnFloyd, &QPushButton::clicked, this, &MainWindow::onFloyd);

    auto* splitter = new QSplitter(Qt::Horizontal);

    auto* leftPanel = new QWidget;
    auto* leftLayout = new QVBoxLayout(leftPanel);
    leftLayout->setContentsMargins(0, 0, 0, 0);
    leftLayout->setSpacing(8);

    auto* graphTitle = new QLabel("Визуализация графа");
    graphTitle->setObjectName("SectionTitle");
    leftLayout->addWidget(graphTitle);

    graphView = new GraphView(leftPanel);
    graphView->setMinimumSize(560, 430);
    leftLayout->addWidget(graphView, 1);
    connect(graphView, &GraphView::vertexClicked,
            this,      &MainWindow::onVertexSelected);

    auto* rightPanel = new QWidget;
    rightPanel->setMinimumWidth(430);
    auto* rightLayout = new QVBoxLayout(rightPanel);
    rightLayout->setContentsMargins(0, 0, 0, 0);
    rightLayout->setSpacing(8);

    tabWidget = new QTabWidget;
    rightLayout->addWidget(tabWidget);

    auto* algoTab    = new QWidget;
    auto* algoLayout = new QVBoxLayout(algoTab);
    algoLayout->setSpacing(8);

    auto* stepsGroup  = new QGroupBox("Шаги алгоритма");
    auto* stepsLayout = new QVBoxLayout(stepsGroup);
    stepList = new QListWidget;
    stepList->setMinimumHeight(150);
    stepsLayout->addWidget(stepList);
    algoLayout->addWidget(stepsGroup);
    connect(stepList, &QListWidget::currentRowChanged,
            this, &MainWindow::onStepSelected);

    auto* outGroup  = new QGroupBox("Результат");
    auto* outLayout = new QVBoxLayout(outGroup);
    outputLog = new QTextEdit;
    outputLog->setReadOnly(true);
    outputLog->setMinimumHeight(180);
    outLayout->addWidget(outputLog);
    algoLayout->addWidget(outGroup, 1);

    tabWidget->addTab(algoTab, "Алгоритмы");

    auto* editTab    = new QWidget;
    auto* editLayout = new QVBoxLayout(editTab);
    editLayout->setSpacing(8);

    auto* vGroup  = new QGroupBox("Операции с вершинами");
    auto* vLayout = new QFormLayout(vGroup);
    vertexNameEdit = new QLineEdit;
    vertexNameEdit->setPlaceholderText("например: 7");
    auto* btnAddV = new QPushButton("Добавить вершину");
    btnAddV->setObjectName("Success");
    vLayout->addRow("Имя новой вершины:", vertexNameEdit);
    vLayout->addRow("", btnAddV);

    removeVertexCombo = new QComboBox;
    auto* btnRemV = new QPushButton("Удалить вершину");
    btnRemV->setObjectName("Danger");
    vLayout->addRow("Вершина для удаления:", removeVertexCombo);
    vLayout->addRow("", btnRemV);
    editLayout->addWidget(vGroup);

    connect(btnAddV, &QPushButton::clicked, this, &MainWindow::onAddVertex);
    connect(btnRemV, &QPushButton::clicked, this, &MainWindow::onRemoveVertex);

    auto* eGroup  = new QGroupBox("Операции с рёбрами");
    auto* eLayout = new QFormLayout(eGroup);
    editFromCombo = new QComboBox;
    editToCombo   = new QComboBox;
    weightSpin    = new QSpinBox;
    weightSpin->setRange(1, 9999);
    weightSpin->setValue(1);
    weightSpin->setSuffix(" вес");

    auto* btnAddE = new QPushButton("Добавить / обновить ребро");
    btnAddE->setObjectName("Success");
    auto* btnRemE = new QPushButton("Удалить ребро");
    btnRemE->setObjectName("Danger");

    eLayout->addRow("Из вершины:", editFromCombo);
    eLayout->addRow("В вершину:",  editToCombo);
    eLayout->addRow("Вес ребра:",  weightSpin);
    eLayout->addRow("", btnAddE);
    eLayout->addRow("", btnRemE);
    editLayout->addWidget(eGroup);
    editLayout->addStretch();

    connect(btnAddE, &QPushButton::clicked, this, &MainWindow::onAddEdge);
    connect(btnRemE, &QPushButton::clicked, this, &MainWindow::onRemoveEdge);

    auto* utilGroup  = new QGroupBox("Управление графом");
    auto* utilLayout = new QHBoxLayout(utilGroup);
    auto* btnLoad  = new QPushButton("Граф из задания");
    auto* btnClear = new QPushButton("Очистить всё");
    btnClear->setObjectName("Danger");
    utilLayout->addWidget(btnLoad);
    utilLayout->addWidget(btnClear);
    editLayout->addWidget(utilGroup);

    connect(btnLoad,  &QPushButton::clicked, this, &MainWindow::onLoadDefault);
    connect(btnClear, &QPushButton::clicked, this, &MainWindow::onClearGraph);

    tabWidget->addTab(editTab, "Редактор графа");

    auto* matTab    = new QWidget;
    auto* matLayout = new QVBoxLayout(matTab);

    auto* matInfo = new QLabel(
        "Матрица смежности / весов.  "
        "0 = ребра нет.  "
        "Ячейку можно редактировать прямо в таблице.");
    matInfo->setWordWrap(true);
    matLayout->addWidget(matInfo);

    matrixTable = new QTableWidget;
    matLayout->addWidget(matrixTable, 1);
    connect(matrixTable, &QTableWidget::cellChanged,
            this, &MainWindow::onMatrixChanged);

    tabWidget->addTab(matTab, "Матрица");

    splitter->addWidget(leftPanel);
    splitter->addWidget(rightPanel);
    splitter->setStretchFactor(0, 1);
    splitter->setStretchFactor(1, 0);
    splitter->setSizes({900, 470});
    mainLayout->addWidget(splitter);
}

// ═══════════════════════════════════════════════════════
//  МЕНЮ
// ═══════════════════════════════════════════════════════
void MainWindow::setupMenus() {
    auto* mb = menuBar();
    mb->setStyleSheet(
        "QMenuBar { background:#161b22; color:#c9d1d9; border-bottom:1px solid #30363d; }"
        "QMenuBar::item:selected { background:#30363d; }"
        "QMenu { background:#161b22; color:#c9d1d9; border:1px solid #30363d; }"
        "QMenu::item:selected { background:#1f6feb; }"
        "QMenu::separator { background:#30363d; height:1px; margin:4px 0; }");

    // Файл
    auto* fileMenu = mb->addMenu("Файл");
    fileMenu->addAction("Загрузить граф из задания", this, &MainWindow::onLoadDefault);
    fileMenu->addSeparator();
    fileMenu->addAction("Очистить граф", this, &MainWindow::onClearGraph);

    // Алгоритмы
    auto* algoMenu = mb->addMenu("Алгоритмы");
    algoMenu->addAction("Обход в ширину (BFS)",  this, &MainWindow::onBFS);
    algoMenu->addAction("Обход в глубину (DFS)", this, &MainWindow::onDFS);
    algoMenu->addSeparator();
    algoMenu->addAction("Алгоритм Дейкстры",     this, &MainWindow::onDijkstra);
    algoMenu->addAction("Алгоритм Флойда",        this, &MainWindow::onFloyd);

    // Справка
    auto* helpMenu = mb->addMenu("Справка");
    helpMenu->addAction("О программе", [this]() {
        QMessageBox::about(this, "О программе",
            "<b>Визуализатор алгоритмов на графах</b><br><br>"
            "<b>Реализованные алгоритмы:</b><br>"
            "&nbsp;&nbsp;• Обход в ширину (BFS)<br>"
            "&nbsp;&nbsp;• Обход в глубину (DFS)<br>"
            "&nbsp;&nbsp;• Алгоритм Дейкстры<br>"
            "&nbsp;&nbsp;• Алгоритм Флойда–Уоршелла<br><br>"
            "<b>Граф:</b> ориентированный взвешенный<br>"
            "<b>Лабораторная работа №2</b><br>"
            "Вершины: 1–6 &nbsp; Старт: вершина 5<br><br>"
            "Разработано на <b>Qt / C++17</b><br>"
            "Визуализация: QGraphicsView");
    });
    helpMenu->addAction("Как пользоваться", [this]() {
        QMessageBox::information(this, "Как пользоваться",
            "1. Выберите начальную вершину в выпадающем списке.\n"
            "2. (Для Дейкстры/Флойда) выберите конечную вершину.\n"
            "3. Нажмите кнопку нужного алгоритма.\n"
            "4. Пошаговый журнал — в левом списке.\n"
            "5. Итоговый результат — в поле «Результат».\n\n"
            "Редактирование:\n"
            "• Вкладка «Редактирование» — добавить/удалить вершину или ребро.\n"
            "• Вкладка «Матрица смежности» — вручную изменить ячейку.\n"
            "• Клик по вершине на графе — выбирает её как начальную.\n"
            "• Колёсико мыши — масштаб графа.");
    });
}

// ═══════════════════════════════════════════════════════
//  ОБНОВЛЕНИЕ UI
// ═══════════════════════════════════════════════════════
void MainWindow::refreshVertexLists() {
    int n = graph.vertexCount();
    auto refill = [&](QComboBox* cb) {
        cb->blockSignals(true);
        int prev = cb->currentIndex();
        cb->clear();
        for (int i = 0; i < n; i++)
            cb->addItem(QString::fromStdString(graph.vertexName(i)));
        cb->setCurrentIndex(std::clamp(prev, 0, n - 1));
        cb->blockSignals(false);
    };
    refill(startVertexCombo);
    refill(endVertexCombo);
    refill(editFromCombo);
    refill(editToCombo);
    refill(removeVertexCombo);

    // Начальная вершина по умолчанию — 5 (индекс 4)
    if (n >= 5) startVertexCombo->setCurrentIndex(4);
}

void MainWindow::refreshMatrix() {
    matrixUpdating = true;
    int n = graph.vertexCount();
    matrixTable->setRowCount(n);
    matrixTable->setColumnCount(n);

    QStringList headers;
    for (int i = 0; i < n; i++)
        headers << QString::fromStdString(graph.vertexName(i));
    matrixTable->setHorizontalHeaderLabels(headers);
    matrixTable->setVerticalHeaderLabels(headers);

    const auto& mat = graph.adjacencyMatrix();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            auto* item = new QTableWidgetItem(QString::number(mat[i][j]));
            item->setTextAlignment(Qt::AlignCenter);
            item->setBackground(
                mat[i][j] != 0 ? QColor("#0d419d") : QColor("#0d1117"));
            matrixTable->setItem(i, j, item);
        }
    }
    matrixTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    matrixTable->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    matrixUpdating = false;
}

void MainWindow::refreshGraph() {
    graphView->clearHighlights();
    graphView->refresh();
    refreshMatrix();
    refreshVertexLists();
}

// ═══════════════════════════════════════════════════════
//  СЛОТЫ — МАТРИЦА / ВЕРШИНА
// ═══════════════════════════════════════════════════════
void MainWindow::onMatrixChanged(int row, int col) {
    if (matrixUpdating) return;
    auto* item = matrixTable->item(row, col);
    if (!item) return;
    bool ok;
    int val = item->text().toInt(&ok);
    if (!ok || val < 0) { refreshMatrix(); return; }
    if (val == 0) graph.removeEdge(row, col);
    else          graph.addEdge(row, col, val);
    matrixUpdating = true;
    item->setBackground(val != 0 ? QColor("#0d419d") : QColor("#0d1117"));
    matrixUpdating = false;
    graphView->refresh();
}

void MainWindow::onVertexSelected(int idx) {
    if (idx >= 0 && idx < startVertexCombo->count())
        startVertexCombo->setCurrentIndex(idx);
}

void MainWindow::onStepSelected(int /*row*/) {}

// ═══════════════════════════════════════════════════════
//  ВЫВОД ШАГОВ
// ═══════════════════════════════════════════════════════
void MainWindow::showSteps(const QStringList& steps, const QString& title) {
    stepList->clear();
    for (const auto& s : steps)
        stepList->addItem(s.trimmed().left(130));
    outputLog->setPlainText(title + "\n\n" + steps.join("\n---\n"));
}

// ═══════════════════════════════════════════════════════
//  АЛГОРИТМЫ
// ═══════════════════════════════════════════════════════
void MainWindow::onBFS() {
    int start = startVertexCombo->currentIndex();
    if (start < 0 || graph.vertexCount() == 0) return;

    auto res = graph.bfs(start);
    QStringList steps;
    for (const auto& s : res.steps)
        steps << QString::fromStdString(s);

    showSteps(steps,
        "Обход в ширину (BFS) от вершины " +
        QString::fromStdString(graph.vertexName(start)));

    graphView->highlightVertices(res.visitOrder);
    tabWidget->setCurrentIndex(0);
}

void MainWindow::onDFS() {
    int start = startVertexCombo->currentIndex();
    if (start < 0 || graph.vertexCount() == 0) return;

    auto res = graph.dfs(start);
    QStringList steps;
    for (const auto& s : res.steps)
        steps << QString::fromStdString(s);

    showSteps(steps,
        "Обход в глубину (DFS) от вершины " +
        QString::fromStdString(graph.vertexName(start)));

    graphView->highlightVertices(res.visitOrder);
    tabWidget->setCurrentIndex(0);
}

void MainWindow::onDijkstra() {
    int start = startVertexCombo->currentIndex();
    int end   = endVertexCombo->currentIndex();
    if (start < 0 || graph.vertexCount() == 0) return;

    auto res = graph.dijkstra(start);
    QStringList steps;
    for (const auto& s : res.steps)
        steps << QString::fromStdString(s);

    showSteps(steps,
        "Алгоритм Дейкстры от вершины " +
        QString::fromStdString(graph.vertexName(start)));

    // Показываем путь до конечной вершины
    if (end >= 0 && end != start) {
        auto path = graph.getPath(res.prev, end);
        QString extra;
        if (!path.empty() && res.dist[end] < INF) {
            extra  = "\nКратчайший путь от вершины ";
            extra += QString::fromStdString(graph.vertexName(start));
            extra += " до вершины ";
            extra += QString::fromStdString(graph.vertexName(end));
            extra += ":\n  ";
            for (int v : path)
                extra += QString::fromStdString(graph.vertexName(v)) + " → ";
            extra.chop(3);
            extra += "\n  Стоимость: " + QString::number(res.dist[end]);
            graphView->highlightPath(path);
        } else {
            extra  = "\nПути от вершины ";
            extra += QString::fromStdString(graph.vertexName(start));
            extra += " до вершины ";
            extra += QString::fromStdString(graph.vertexName(end));
            extra += " — не существует.";
        }
        outputLog->append(extra);
    }
    tabWidget->setCurrentIndex(0);
}

void MainWindow::onFloyd() {
    if (graph.vertexCount() == 0) return;

    auto res = graph.floyd();
    QStringList steps;
    for (const auto& s : res.steps)
        steps << QString::fromStdString(s);

    showSteps(steps, "Алгоритм Флойда–Уоршелла (кратчайшие пути между всеми парами вершин)");

    // Путь между выбранными вершинами
    int s = startVertexCombo->currentIndex();
    int e = endVertexCombo->currentIndex();
    if (s >= 0 && e >= 0 && s != e) {
        auto path = graph.floydPath(res, s, e);
        if (!path.empty()) {
            QString extra  = "\nПуть (Флойд): ";
            extra += QString::fromStdString(graph.vertexName(s));
            extra += " → ";
            extra += QString::fromStdString(graph.vertexName(e));
            extra += ":\n  ";
            for (int v : path)
                extra += QString::fromStdString(graph.vertexName(v)) + " → ";
            extra.chop(3);
            if (res.dist[s][e] < INF)
                extra += "\n  Стоимость: " + QString::number(res.dist[s][e]);
            outputLog->append(extra);
            graphView->highlightPath(path);
        } else {
            outputLog->append(
                "\nПути между выбранными вершинами нет.");
        }
    }
    tabWidget->setCurrentIndex(0);
}

// ═══════════════════════════════════════════════════════
//  РЕДАКТИРОВАНИЕ ГРАФА
// ═══════════════════════════════════════════════════════
void MainWindow::onAddVertex() {
    QString name = vertexNameEdit->text().trimmed();
    if (name.isEmpty()) name = QString::number(graph.vertexCount() + 1);
    graph.addVertex(name.toStdString());
    vertexNameEdit->clear();
    graphView->autoLayout();
    refreshGraph();
}

void MainWindow::onRemoveVertex() {
    int idx = removeVertexCombo->currentIndex();
    if (!graph.removeVertex(idx)) return;
    graphView->autoLayout();
    refreshGraph();
}

void MainWindow::onAddEdge() {
    int f = editFromCombo->currentIndex();
    int t = editToCombo->currentIndex();
    int w = weightSpin->value();
    if (f == t) {
        QMessageBox::warning(this, "Ошибка",
            "Петли (ребро из вершины в саму себя) не поддерживаются.");
        return;
    }
    graph.addEdge(f, t, w);
    refreshGraph();
}

void MainWindow::onRemoveEdge() {
    graph.removeEdge(editFromCombo->currentIndex(),
                     editToCombo->currentIndex());
    refreshGraph();
}

void MainWindow::onSetWeight() {
    graph.setEdgeWeight(editFromCombo->currentIndex(),
                        editToCombo->currentIndex(),
                        weightSpin->value());
    refreshGraph();
}

void MainWindow::onLoadDefault() {
    graph.loadDefaultGraph();
    graphView->autoLayout();   // позиции берутся точно из методички
    refreshGraph();

    outputLog->setPlainText(
        "Граф из лабораторной работы №2 загружен.\n\n"
        "Вершины: 1, 2, 3, 4, 5, 6\n"
        "Тип: ориентированный взвешенный граф\n\n"
        "Рёбра:\n"
        "  5 → 2 : 21\n"
        "  5 → 3 : 30\n"
        "  2 → 4 : 20\n"
        "  2 → 1 : 28\n"
        "  4 → 2 : 39\n"
        "  4 → 1 : 15\n"
        "  4 → 6 : 31\n"
        "  3 → 1 : 13\n"
        "  6 → 1 : 18\n\n"
        "Выберите алгоритм и нажмите кнопку.\n"
        "Начальная вершина по умолчанию: 5."
    );
    startVertexCombo->setCurrentIndex(4);
}

void MainWindow::onClearGraph() {
    auto r = QMessageBox::question(this,
                                   "Очистить граф",
                                   "Удалить все вершины и рёбра?",
                                   QMessageBox::Yes | QMessageBox::No);
    if (r == QMessageBox::Yes) {
        graph.clear();
        refreshGraph();
        outputLog->clear();
        stepList->clear();
    }
}
