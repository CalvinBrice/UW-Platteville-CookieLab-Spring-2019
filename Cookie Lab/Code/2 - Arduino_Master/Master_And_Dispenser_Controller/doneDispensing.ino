bool doneDispensing(int bay, int quantity) {
  mode = DISPENSE;
  switch (bay) {
    case 0:
      butter(quantity, mode);
      return true;
      break;
    case 1:
      sugar(quantity, mode);
      return true;
      break;
    case 2:
      molasses(quantity, mode);
      return true;
      break;
    case 3:
      vanilla(quantity, mode);
      return true;
      break;
    case 4:
      egg(quantity, mode);
      return true;
      break;
    case 5:
      mms(quantity, mode);
      return true;
      break;
    case 6:
      chocolateChips(quantity, mode);
      return true;
      break;
    case 7:
      salt(quantity, mode);
      return true;
      break;
    case 8:
      bakingSoda(quantity, mode);
      return true;
      break;
    case 9:
      flour(quantity, mode);
      return true;
      break;
    case 10:
      oats(quantity, mode);
      return true;
      break;
    default:
      break;
  }
}

