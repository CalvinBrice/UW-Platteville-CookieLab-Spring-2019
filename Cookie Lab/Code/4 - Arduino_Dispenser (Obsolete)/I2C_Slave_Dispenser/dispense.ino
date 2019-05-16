bool dispense() {
  mode = DISPENSE;
  switch (bay) {
    case 0:
      butter();
      return true;
      break;
    case 1:
      sugar();
      return true;
      break;
    case 2:
      molasses();
      return true;
      break;
    case 3:
      vanilla();
      return true;
      break;
    case 4:
      egg();
      return true;
      break;
    case 5:
      mms();
      return true;
      break;
    case 6:
      chocolateChips();
      return true;
      break;
    case 7:
      salt();
      return true;
      break;
    case 8:
      bakingSoda();
      return true;
      break;
    case 9:
      flour();
      return true;
      break;
    case 10:
      oats();
      return true;
      break;
    default:
      break;
  }
}

