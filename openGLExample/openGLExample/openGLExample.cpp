#include "openGLExample.h"


MyGLWidget::MyGLWidget(QWidget* parent)
	: QOpenGLWidget(parent)
{
	// 생성자에서는 특별한 초기화가 필요 없습니다.
}

MyGLWidget::~MyGLWidget()
{
	// 리소스 정리: Context가 현재 상태일 때 수행해야 함
	makeCurrent();
	delete m_program;
	m_vbo.destroy();
	m_vao.destroy();
	doneCurrent();
}

void MyGLWidget::initializeGL()
{
	// 1. OpenGL 함수 로드 (필수)
	initializeOpenGLFunctions();

	// 2. 배경색 지정 (검은색)
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// 3. 쉐이더 프로그램 생성 및 컴파일
	m_program = new QOpenGLShaderProgram();

	// Vertex Shader (정점 위치 결정)
	m_program->addShaderFromSourceCode(QOpenGLShader::Vertex,
		"#version 330 core\n"
		"layout(location = 0) in vec3 position;\n"
		"void main() {\n"
		"   gl_Position = vec4(position, 1.0);\n"
		"}");

	// Fragment Shader (픽셀 색상 결정 - 주황색)
	m_program->addShaderFromSourceCode(QOpenGLShader::Fragment,
		"#version 330 core\n"
		"out vec4 color;\n"
		"void main() {\n"
		"   color = vec4(1.0, 0.5, 0.2, 1.0);\n"
		"}");

	m_program->link();
	m_program->bind();

	// 4. 삼각형 정점 데이터 정의 (x, y, z)
	float vertices[] = {
		-0.5f, -0.5f, 0.0f, // 왼쪽 아래
		 0.5f, -0.5f, 0.0f, // 오른쪽 아래
		 0.0f,  0.5f, 0.0f  // 위쪽 중앙
	};

	// 5. VAO (Vertex Array Object) 생성 및 바인딩
	m_vao.create();
	m_vao.bind();

	// 6. VBO (Vertex Buffer Object) 생성 및 데이터 전송
	m_vbo.create();
	m_vbo.bind();
	m_vbo.allocate(vertices, sizeof(vertices));

	// 7. 정점 속성 설정 (location 0 = position)
	// 인자: location, type, offset, tupleSize, stride
	m_program->enableAttributeArray(0);
	m_program->setAttributeBuffer(0, GL_FLOAT, 0, 3, 0);

	// 8. 바인딩 해제 (상태 복구)
	m_vao.release();
	m_vbo.release();
	m_program->release();
}

void MyGLWidget::resizeGL(int w, int h)
{
	// 뷰포트 설정
	glViewport(0, 0, w, h);
}

void MyGLWidget::paintGL()
{
	// 1. 화면 지우기
	glClear(GL_COLOR_BUFFER_BIT);

	// 2. 쉐이더 및 VAO 사용
	m_program->bind();
	m_vao.bind();

	// 3. 그리기 (삼각형)
	glDrawArrays(GL_TRIANGLES, 0, 3);

	// 4. 해제
	m_vao.release();
	m_program->release();
}
