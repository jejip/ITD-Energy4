void movesteppers() {
    
    //disable stepper motors when it gets the command
    //motors will enable automatically when they receive a move command.
    
    if (stepper1_enable != stepper1_enable_last) { //poll for changes, then disable motor on change 
      if (stepper1_enable) 
        myStepper1->release();
      
      stepper1_enable_last = stepper1_enable; //set the last state to the current state
    }
    
    if (stepper2_enable != stepper2_enable_last) { //only fire when the state has been changed
      if (stepper2_enable) 
        myStepper2->release();
     
      stepper2_enable_last = stepper2_enable; //set the last state to the current state
    }
    

    
  // move steppers
  
  //move stepper 1
  if (stepper1.distanceToGo() == 0) {//only give off the command to move when the destination has been reached
      stepper1.moveTo(stepper1_pos);
    }
    else {
      stepper1.setSpeed(stepper1_speed);
      stepper1.runSpeedToPosition(); //only runs one way? but this is fine...
    }
//  stepper1.run();

  //todo: only run if rotary > 0
  
  
  //move stepper 2
  if (stepper2.distanceToGo() == 0) {
      stepper2.moveTo(stepper2_pos);
    }
  stepper2.run();

  //set speed
//  stepper1.setSpeed(stepper1_speed);
//  stepper2.setSpeed(stepper2_speed);  
}

