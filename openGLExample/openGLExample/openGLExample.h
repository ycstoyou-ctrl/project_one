#pragma once
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>

class MyGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
	Q_OBJECT

public:
	MyGLWidget(QWidget* parent = nullptr);
	~MyGLWidget();

protected:
	void initializeGL() override;
	void resizeGL(int w, int h) override;
	void paintGL() override;

private:
	// 쉐이더 프로그램 (Vertex & Fragment Shader)
	QOpenGLShaderProgram* m_program = nullptr;

	// VBO: 정점 데이터 버퍼
	QOpenGLBuffer m_vbo;

	// VAO: 정점 속성 정의
	QOpenGLVertexArrayObject m_vao;
};
