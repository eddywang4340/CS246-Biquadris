#include "constants.h"
#include "<map>"
#include "xwindow.h"

const int GAME_NUM_ROW = 18;
const int GAME_NUM_COL = 11;
const int SHAPE_GRID_NUM_ROW = 4;
const int SHAPE_GRID_NUM_COL = 4;
const std::map<char, int> CHAR_TO_COLOUR = {{'L': Xwindow::Black},
                                            {'I': Xwindow::Red},
                                            {'J': Xwindow::Green},
                                            {'O': Xwindow::Blue},
                                            {'S': Xwindow::Orange},
                                            {'Z': Xwindow::Yellow},
                                            {'T': Xwindow::Purple},
                                            {'*': Xwindow::Brown},
                                            {' ': Xwindow::White}}
