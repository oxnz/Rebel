//
//  RectEngine.hpp
//  Rebel
//
//  Created by 云心逸 on 2019/3/23.
//  Copyright © 2019 云心逸. All rights reserved.
//

#ifndef RectEngine_hpp
#define RectEngine_hpp

#include <vector>
#include <random>
#include <iostream>
#include <algorithm>
#include "Engine.hpp"
#include "Rect.hpp"

class RectEngine : public Engine {
private:
	int m_nrow;
	int m_ncol;
	int m_timeout;
	std::mt19937 m_random_engine;
	std::uniform_int_distribution<int> m_index_dist;
	std::uniform_int_distribution<int> m_color_dist;
	std::vector<Rect> m_shapes;
private:
	void split() {
		float xstep = 1.0/m_ncol, ystep = 1.0/m_nrow;
		Rect shape(0, {0, 0}, {xstep, ystep});
		std::vector<Rect> shapes(m_nrow*m_ncol, shape);
		for (int i = 0; i < m_nrow; ++i) {
			for (int j = 0; j < m_ncol; ++j) {
				auto& rect = shapes.at(i*m_ncol+j);
				rect.move(xstep*j, ystep*i);
			}
		}
		m_index_dist.param(std::uniform_int_distribution<int>::param_type(0,
																		  static_cast<int>(shapes.size())));
		m_shapes.swap(shapes);
	}
public:
	RectEngine(int nrow, int ncol, int timeout) : Engine(timeout),
	m_nrow(nrow), m_ncol(ncol), m_random_engine(),
	m_index_dist(0, m_nrow*m_ncol-1), m_color_dist(-128, 127), m_shapes() {
		split();
	}

	void display() {
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		for (const auto& shape : m_shapes) {
			glColor4bv(shape.colorv);
			shape.draw();
		}
		glutSwapBuffers();
	}

	void reshape(int w, int h) {
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(0, 1, 0, 1);
	}

	void transform() {
		auto index = m_index_dist(m_random_engine);
		auto &shape = m_shapes[index];
		if (shape.color == 0)
			for (int i = 0; i < 4; ++i)
				shape.colorv[i] = m_color_dist(m_random_engine);
		else for (int i = 0; i < 4; ++i) shape.colorv[i] += 2;
	}

	void processTimeout(int timer) {
		transform();
		glutPostRedisplay();
	}

	void sort() {
		std::cout << __PRETTY_FUNCTION__ << "\n";
		std::vector<int32_t> colors(m_shapes.size());
		for (int i = 0; i < m_shapes.size(); ++i)
			colors[i] = m_shapes[i].color;
		std::sort(colors.begin(), colors.end());
		for (int i = 0; i < m_shapes.size(); ++i)
			m_shapes[i].color = colors[i];
	}

	virtual void processNormalKeystoke(unsigned char key, int x, int y) {
		std::cout << __PRETTY_FUNCTION__ << key << "\n";
		switch (key) {
			case ' ':
				sort();
				glutPostRedisplay();
				break;
			default:
				break;
		}
	}
	
	void processSpecialKeystroke(int key, int x, int y) {
//		int mask = glutGetModifiers();
		switch (key) {
			case GLUT_KEY_LEFT:
				m_ncol *= 0.9;
				if (m_ncol == 0) m_ncol = 1;
				split();
				glutPostRedisplay();
				return;
			case GLUT_KEY_RIGHT:
				m_ncol *= 1.1;
				split();
				glutPostRedisplay();
				return;
			case GLUT_KEY_UP:
				m_nrow *= 1.1;
				split();
				glutPostRedisplay();
				return;
			case GLUT_KEY_DOWN:
				m_nrow *= 0.9;
				if (m_nrow == 0) m_nrow = 1;
				split();
				glutPostRedisplay();
				return;
			default:
				break;
		}
	}
};

#endif /* RectEngine_hpp */
