#pragma once
#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTextEdit>
#include <QTableWidget>
#include <QTabWidget>
#include <QLabel>
#include <QComboBox>
#include <QSpinBox>
#include <QPushButton>
#include <QGroupBox>
#include <QSplitter>
#include <QListWidget>
#include <QDockWidget>
#include "graph.h"
#include "graphview.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr);

private slots:
    void onBFS();
    void onDFS();
    void onDijkstra();
    void onFloyd();
    void onAddVertex();
    void onRemoveVertex();
    void onAddEdge();
    void onRemoveEdge();
    void onSetWeight();
    void onLoadDefault();
    void onClearGraph();
    void onMatrixChanged(int row, int col);
    void onVertexSelected(int idx);
    void onStepSelected(int row);
    void refreshMatrix();
    void refreshGraph();
    void refreshVertexLists();

private:
    void setupUi();
    void setupMenus();
    void showSteps(const QStringList& steps, const QString& title);
    void highlightPath(const std::vector<int>& path);
    void highlightTraversal(const std::vector<int>& order);

    Graph graph;
    GraphView* graphView;
    QGraphicsScene* scene;

    // Tabs
    QTabWidget* tabWidget;

    // Algorithm panel
    QComboBox* startVertexCombo;
    QComboBox* endVertexCombo;
    QTextEdit* outputLog;
    QListWidget* stepList;

    // Edit panel
    QComboBox* editFromCombo;
    QComboBox* editToCombo;
    QSpinBox* weightSpin;
    QLineEdit* vertexNameEdit;
    QComboBox* removeVertexCombo;

    // Matrix tab
    QTableWidget* matrixTable;
    bool matrixUpdating = false;

    // Floyd matrices
    QTabWidget* floydTabs;

    std::vector<int> currentHighlightPath;
    std::vector<int> currentTraversal;
};
