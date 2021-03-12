package com.gshs;
import robocode.*;

public class Gshs_20119_1 extends Robot
{
	public void run() { // Full behavior pipeline
		for(int i=0; i<4; i++){ turnRight(90); ahead(100); }
		while(true) { } // repeat behavior
	}

	public void onScannedRobot(ScannedRobotEvent e) { fire(1); } // when see other robot

	public void onHitByBullet(HitByBulletEvent e) { back(10); } // when get hit by a bullet
	
	public void onHitWall(HitWallEvent e) { back(20); } // when touch the wall	
}
