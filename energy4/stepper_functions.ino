void movesteppers() {
    
    //enable or disable stepper motors when it gets the command
    bool stepper1_enable_last = 0;
    bool stepper2_enable_last = 0;
        
    if (stepper1_enable != stepper1_enable_last) { //only fire when the state has been changed
      if (stepper1_enable) {
        stepper1.enableOutputs(); 
      }
      else {
        stepper1.disableOutputs();
      }
      stepper1_enable_last = stepper1_enable; //set the last state to the current state
    }
    
    //...duplicate for 2nd stepper motor
    
  
  //move stepper 1
  if (stepper1.distanceToGo() == 0) {//only give off the command to move when the destination has been reached
      stepper1.moveTo(stepper1_pos);
    }
  stepper1.run();
  
  //move stepper 2
  if (stepper2.distanceToGo() == 0) {
      stepper2.moveTo(stepper2_pos);
    }
  stepper2.run();

}

