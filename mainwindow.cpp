#include "mainwindow.h"
#include "gamecontroller.h"

#include <QLayout>
#include <QInputEvent>
#include <QRandomGenerator>
#include <QLabel>
#include <QJsonDocument>

MainWindow::MainWindow(GameController* gameController,
                       Snake* snake)
    : QWidget{nullptr},
      view {new QGraphicsView},
      scene {new QGraphicsScene},
      menu {new Menu{gameController}},
      stackedLayout {new QStackedLayout}
{
    setFocusPolicy(Qt::StrongFocus);
    // Window
    setWindowTitle("SnakePorcoDio");
    setFocus();

    // View
    scene->setBackgroundBrush(Qt::black);
    scene->setSceneRect(0,0,400,300);
    view->setScene(scene);
    view->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    view->setFrameShape(QGraphicsView::NoFrame);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setRenderHint(QPainter::Antialiasing);
    view->setFixedSize(400,300);
    view->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

    // Status bar
    auto labelWidget = new QWidget;
    auto labelLayout = new QHBoxLayout;
    auto lengthLabel = new QLabel{"1"};
    lengthLabel->setStyleSheet("font-weight: bold");
    auto lengthText  = new QLabel{"SCORE:"};
    lengthText->setStyleSheet("font-weight: bold");
    labelLayout->addWidget(lengthText);
    labelLayout->addWidget(lengthLabel);
    labelWidget->setLayout(labelLayout);
//    auto speedLabel = new QLabel{QString::number(1000/time)};
//    speedLabel->setStyleSheet("font-weight: bold");
    auto speedText = new QLabel{"SPEED:"};
    speedText->setStyleSheet("font-weight: bold");
    labelLayout->addWidget(speedText);
//    labelLayout->addWidget(speedLabel);

    // Stacked Layout
    stackedLayout->addWidget(view);
    stackedLayout->addWidget(menu);

    auto layout = new QVBoxLayout;
    layout->setContentsMargins(0,0,0,0);
    //layout->addWidget(view);
    layout->addLayout(stackedLayout);
    layout->addWidget(labelWidget);

    setLayout(layout);

    scene->addItem(snake->getHead());


    scene->addItem(gameController->getFruit());

//    connect(snake, &Snake::lengthChanged,
//            lengthLabel, &QLabel::setText);
//    connect(this, &MainWindow::speedChanged,
//            speedLabel, &QLabel::setText);
    connect(this, &MainWindow::keyPressed,
            gameController, &GameController::keyHandler);
}

MainWindow::~MainWindow()
{
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    emit keyPressed(event);
}

void MainWindow::showMenu() const
{
    stackedLayout->setCurrentWidget(menu);
}

QGraphicsScene* MainWindow::getScene() const
{
    return scene;
}

void MainWindow::closeMenu() const
{
    stackedLayout->setCurrentWidget(view);
}
