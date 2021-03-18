package com.gshs;
import robocode.*;

public class Gshs_20119_4 extends Robot
{
	public void run() { // Full behavior pipeline
		while(true){ turnGunRight(360); }
	}

	public void onScannedRobot(ScannedRobotEvent e) { 
		turnRight(e.getBearing()); fire(1);
		ahead(e.getDistance());
	} // when see other robot

	public void onHitByBullet(HitByBulletEvent e) { back(10); } // when get hit by a bullet
	
	public void onHitWall(HitWallEvent e) { back(20); } // when touch the wall	
}
