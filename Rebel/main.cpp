//
//  main.cpp
//  Rebel
//
//  Created by 云心逸 on 2019/3/23.
//  Copyright © 2019 云心逸. All rights reserved.
//

#include <vector>
#include <string>
#include <random>
#include <memory>
#include <iostream>

#include "RectEngine.hpp"

std::unique_ptr<Engine> G(new RectEngine(5, 6, 5));
void onDisplay() { G->display(); }
void onReshape(int w, int h) { G->reshape(w, h); }
void onTimer(int timer) {
	G->processTimeout(timer);
	glutTimerFunc(G->timeout(), onTimer, timer);
}
void onNormalKeystroke(unsigned char key, int x, int y) {
	G->processNormalKeystoke(key, x, y);
}
void onSpecialKeystroke(int key, int x, int y) {
	G->processSpecialKeystroke(key, x, y);
}

int main(int argc, const char * argv[]) {
	glutInit(&argc, const_cast<char**>(argv));
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE | GLUT_DEPTH);
	{
		int W = glutGet(GLUT_SCREEN_WIDTH), H = glutGet(GLUT_SCREEN_HEIGHT);
		float ratio = 0.5;
		glutInitWindowPosition(((1-ratio)*W)/2, ((1-ratio)*H)/2);
		glutInitWindowSize(ratio*W, ratio*H);
	}
	glutCreateWindow("Rebel");
	{
		glEnable(GL_POINT_SMOOTH);
		glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
		glEnable(GL_LINE_SMOOTH);
		glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
		glEnable(GL_POLYGON_SMOOTH);
		glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
		glHint(GL_FOG_HINT, GL_NICEST);
//		glCullFace (GL_BACK);
//		glEnable (GL_CULL_FACE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA_SATURATE, GL_ONE);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	{ // install callbacks
		glutDisplayFunc(onDisplay);
		glutReshapeFunc(onReshape);
		glutTimerFunc(G->timeout(), onTimer, 0);
		glutKeyboardFunc(onNormalKeystroke);
		glutSpecialFunc(onSpecialKeystroke);
	}
	glutMainLoop();
	return 0;
}
