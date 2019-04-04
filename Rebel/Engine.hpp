//
//  Engine.hpp
//  Rebel
//
//  Created by 云心逸 on 2019/3/23.
//  Copyright © 2019 云心逸. All rights reserved.
//

#ifndef Engine_hpp
#define Engine_hpp

#ifndef GL_SILENCE_DEPRECATION
#define GL_SILENCE_DEPRECATION
#endif

#include <GLUT/GLUT.h>
#include <iostream>

class Engine {
private:
	int m_timeout;
public:
	Engine(int timeout) : m_timeout(timeout) {}
	int timeout() const { return m_timeout; }
	virtual void display() {}
	virtual void reshape(int w, int h) {}
	virtual void processTimeout(int timer) {}
	virtual void processNormalKeystoke(unsigned char key, int x, int y) {}
	virtual void processSpecialKeystroke(int key, int x, int y) {
		std::cout << __PRETTY_FUNCTION__ << ":" << key << ", timeout: " << m_timeout <<  "\n";
		switch (key) {
			case GLUT_KEY_RIGHT:
				m_timeout *= 1.1;
				break;
			case GLUT_KEY_LEFT:
				m_timeout *= 0.9;
				break;
			default:
				break;
		}
	}
};

#endif /* Engine_hpp */
