#pragma once

struct Prm
{

	int NumAgents = 10;

	int NumObstacles = 7;
	int MinObstacleRadius = 10;
	int MaxObstacleRadius = 30;



	//number of horizontal cells used for spatial partitioning
	int NumCellsX = 7;
	//number of vertical cells used for spatial partitioning
	int NumCellsY = 7;


	//how many samples the smoother will use to average a value
	int NumSamplesForSmoothing = 10;


	//this is used to multiply the steering force AND all the multipliers
	//found in SteeringBehavior
	double SteeringForceTweaker = 200.0;

	double SteeringForce = 2.0;
	double MaxSpeed = 150.0;
	double VehicleMass = 1.0;
	double VehicleScale = 3.0;

	//use these values to tweak the amount that each steering force
	//contributes to the total steering force
	double SeparationWeight = 1.0;
	double AlignmentWeight = 1.0;
	double CohesionWeight = 2.0;
	double ObstacleAvoidanceWeight = 10.0;
	double WallAvoidanceWeight = 10.0;
	double 	WanderWeight = 1.0;
	double 	SeekWeight = 1.0;
	double FleeWeight = 1.0;
	double ArriveWeight = 1.0;
	double PursuitWeight = 1.0;
	double OffsetPursuitWeight = 1.0;
	double InterposeWeight = 1.0;
	double HideWeight = 1.0;
	double 	EvadeWeight = 0.01;
	double FollowPathWeight = 0.05;

	//how close a neighbour must be before an agent perceives it (considers it
	//to be within its neighborhood)
	double ViewDistance = 50.0;

	//used in obstacle avoidance
	double MinDetectionBoxLength = 40.0;

	//used in wall avoidance
	double WallDetectionFeelerLength = 40.0;

	//these are the probabilities that a steering behavior will be used
	//when the Prioritized Dither calculate method is used to sum
	//combined behaviors
	float prWallAvoidance = 0.5;
	double prObstacleAvoidance = 0.5;
	double prSeparation = 0.2;
	double prAlignment = 0.3;
	double prCohesion = 0.6;
	double prWander = 0.8;
	double prSeek = 0.8;
	double prFlee = 0.6;
	double prEvade = 1.0;
	double 	prHide = 0.8;
	double prArrive = 0.5;
};