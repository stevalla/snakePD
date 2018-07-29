#ifndef SNAKE_H
#define SNAKE_H

#include <QObject>

#include "chunksnake.h"

class Snake : public QObject
{
    Q_OBJECT

public:
    enum class Direction { Up, Down, Left, Right, Stop };

    Snake(QPoint position);
    ~Snake() override = default;

    void setDirection(Snake::Direction);
    Direction direction();

    ChunkSnake* getHead();
    ChunkSnake* getTail();

    void changeColor(QColor);

    int getLength() const;
    QList<ChunkSnake*> getChunks() const;   // do NOT use this function to
                                            // modify the chunk list

    void hide();

    void readJSON(const QJsonObject &json);
    void writeJSON(QJsonObject &json) const;

    QColor getCurrentColor() const;

    void cycle();

public slots:
    ChunkSnake* addChunk();

private:
    enum Direction dir;
    QColor currentColor;

    QList<ChunkSnake*> chunks;
};

#endif // SNAKE_H
