#ifndef SCENE3D_H
#define SCENE3D_H

#ifndef __APPLE__
    #include <GL/gl.h>
#endif

#include "Object3D.h"
#include <QVector>

class Scene3D : public Object3D
{
    QVector<Object3D*> objects;
    bool origin;

public:
    explicit Scene3D(const QVector3D& center = QVector3D(),
                     QObject *parent = 0);
    virtual ~Scene3D();

    void drawGeometry(void) const;

    void addObject3D(Object3D* obj);

    virtual Object3D* copy();

    void changeOrigin(bool v);

private:
    void drawOrigin()const;

};

#endif // SCENE3D_H
