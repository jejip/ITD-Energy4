void movesteppers() {
    
    //disable stepper motors when it gets the command
    //motors will enable automatically when they receive a move command.
    
    if (stepper1_enable != stepper1_enable_last) { //poll for changes, then disable motor on change 
      if (stepper1_enable) {
        myStepper1->release();
      }
      stepper1_enable_last = stepper1_enable; //set the last state to the current state
    }
    
    if (stepper2_enable != stepper2_enable_last) { //only fire when the state has been changed
      if (stepper2_enable) {
        myStepper2->release();
      }
      stepper2_enable_last = stepper2_enable; //set the last state to the current state
    }
    

  // move steppers

  //stop when the motor reaches 0 position
  if (rotary == 0) { 
    stepper1.stop();
    stepper1.setCurrentPosition(0);
  }
  
  //move stepper 1
  if (stepper1.distanceToGo() == 0) {//only give off the command to move when the destination has been reached
      stepper1_ready = 1;
      stepper1.moveTo(stepper1_pos);
    }
    else {
      stepper1_ready = 0;
      stepper1.setSpeed(stepper1_speed);
      stepper1.runSpeedToPosition(); //only runs one way? but this is fine...
    }
//  stepper1.run();


  //todo: only run if rotary > 0, use stepper1.stop()
  //todo: when rotary is 0, do stepper1.setCurrentPosition()  (side effect: puts motor speed to 0)
  //todo: move to 0 (e.g. put force on motor) when rotary >400


  
  //move stepper 2
  if (stepper2.distanceToGo() == 0) {
      stepper2_ready = 1;
      stepper2.setAcceleration(stepper2_speed); //change acceleration 
      stepper2.moveTo(stepper2_pos);
    }
    else {
      stepper2_ready = 0;
    }
  stepper2.run();

  //set speed
//  stepper1.setSpeed(stepper1_speed);
//  stepper2.setSpeed(stepper2_speed);  
}

