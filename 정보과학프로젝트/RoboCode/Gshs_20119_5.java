package com.gshs;
import robocode.*;

// all comments written by gs20119
public class Gshs_20119_5 extends AdvancedRobot
{
	public void run() { // Full behavior pipeline
		setAdjustRadarForGunTurn(true); // radar & gun is independent
		setTurnRadarRight(1000); // initial scan
		execute();
		while(true){ 
			if(getRadarTurnRemaining() == 0) setTurnRadarRight(3); // default scanning 
			execute();
		}
	}

	// getHeading = body
	// getGunHeading = gun  // for now, body = gun
	// getBearing = enemy-body  // getBearing + getHeading = enemy
	// getRadarHeading = radar
	
	public void onScannedRobot(ScannedRobotEvent e) { // when radar catches the enemy 
		double bearing = e.getBearing();
		double dist = e.getDistance();
		setTurnRight(bearing); // rotate body(gun) to enemy
		setTurnRadarRight(getHeading()+bearing-getRadarHeading()); 
		// rotate radar to enemy+bearing (movement prediction)
		
		if(Math.abs(getTurnRemaining())<10){ // move & fire
			if(e.getDistance()>200) setAhead(dist/2);
			if(e.getDistance()<100) setBack(dist*2);
			setFire(3);
		}
	}

	public void onHitByBullet(HitByBulletEvent e) { setBack(10); } // when get hit by a bullet
	
	public void onHitWall(HitWallEvent e) { // when touch the wall	
		setBack(20); setTurnRight(90); setAhead(20); // prevent stucking 
	} 
}
