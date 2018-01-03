package joos.lib;

import java.awt.*;

public class JoosConstants extends Object {
  // constants from java.awt.Color
  public Color black()      { return(Color.black);       } 
  public Color blue()       { return(Color.blue);        } 
  public Color cyan()       { return(Color.cyan);        } 
  public Color darkGray()   { return(Color.darkGray);    }
  public Color gray()       { return(Color.gray);        }
  public Color green()      { return(Color.green);       }
  public Color lightGray()  { return(Color.lightGray);   }
  public Color magenta()    { return(Color.magenta);     } 
  public Color orange()     { return(Color.orange);      }
  public Color pink()       { return(Color.pink);        }
  public Color red()        { return(Color.red);         } 
  public Color white()      { return(Color.white);       } 
  public Color yellow()     { return(Color.yellow);      } 

  // constants from java.awt.Cursor
  public int C_DEFAULT_CURSOR() { return(Cursor.DEFAULT_CURSOR);}
  public int C_CROSSHAIR_CURSOR() { return(Cursor.CROSSHAIR_CURSOR);}
  public int C_HAND_CURSOR() { return(Cursor.HAND_CURSOR);}
  public int C_MOVE_CURSOR() { return(Cursor.MOVE_CURSOR);}
  public int C_TEXT_CURSOR() { return(Cursor.TEXT_CURSOR);}
  public int C_WAIT_CURSOR() { return(Cursor.WAIT_CURSOR);}
  public int C_N_RESIZE_CURSOR() { return(Cursor.N_RESIZE_CURSOR);}
  public int C_E_RESIZE_CURSOR() { return(Cursor.E_RESIZE_CURSOR);}
  public int C_W_RESIZE_CURSOR() { return(Cursor.W_RESIZE_CURSOR);}
  public int C_S_RESIZE_CURSOR() { return(Cursor.S_RESIZE_CURSOR);}
  public int C_NE_RESIZE_CURSOR() { return(Cursor.NE_RESIZE_CURSOR);}
  public int C_NW_RESIZE_CURSOR() { return(Cursor.NW_RESIZE_CURSOR);}
  public int C_SE_RESIZE_CURSOR() { return(Cursor.SE_RESIZE_CURSOR);}
  public int C_SW_RESIZE_CURSOR() { return(Cursor.SW_RESIZE_CURSOR);}

  // constants from java.awt.Event

  public int ACTION_EVENT()        { return(Event.ACTION_EVENT);       }
  public int GOT_FOCUS()           { return(Event.GOT_FOCUS);          }
  public int LOST_FOCUS()          { return(Event.LOST_FOCUS);         }
  public int KEY_ACTION()          { return(Event.KEY_ACTION);         }
  public int KEY_ACTION_RELEASE()  { return(Event.KEY_ACTION_RELEASE); }
  public int KEY_PRESS()           { return(Event.KEY_PRESS);          }
  public int KEY_RELEASE()         { return(Event.KEY_RELEASE);        }
  public int LIST_SELECT()         { return(Event.LIST_SELECT);        }
  public int LIST_DESELECT()       { return(Event.LIST_DESELECT);      }
  public int LOAD_FILE()           { return(Event.LOAD_FILE);          }
  public int SAVE_FILE()           { return(Event.SAVE_FILE);          }
  public int MOUSE_DOWN()          { return(Event.MOUSE_DOWN);         }
  public int MOUSE_UP()            { return(Event.MOUSE_UP);           }
  public int MOUSE_DRAG()          { return(Event.MOUSE_DRAG);         }
  public int MOUSE_MOVE()          { return(Event.MOUSE_MOVE);         }
  public int MOUSE_ENTER()         { return(Event.MOUSE_ENTER);        }
  public int MOUSE_EXIT()          { return(Event.MOUSE_EXIT);         }
  public int SCROLL_ABSOLUTE()     { return(Event.SCROLL_ABSOLUTE);    }
  public int SCROLL_LINE_UP()      { return(Event.SCROLL_LINE_UP);     }
  public int SCROLL_LINE_DOWN()    { return(Event.SCROLL_LINE_DOWN);   }
  public int SCROLL_PAGE_UP()      { return(Event.SCROLL_PAGE_UP);     }
  public int SCROLL_PAGE_DOWN()    { return(Event.SCROLL_PAGE_DOWN);   }
  public int WINDOW_EXPOSE()       { return(Event.WINDOW_EXPOSE);      }
  public int WINDOW_ICONIFY()      { return(Event.WINDOW_ICONIFY);     }
  public int WINDOW_DEICONIFY()    { return(Event.WINDOW_DEICONIFY);   }
  public int WINDOW_DESTROY()      { return(Event.WINDOW_DESTROY);     }
  public int WINDOW_MOVED()        { return(Event.WINDOW_MOVED);       }

  public int ALT_MASK()   { return(Event.ALT_MASK);    }
  public int CTRL_MASK()  { return(Event.CTRL_MASK);   }
  public int META_MASK()  { return(Event.META_MASK);   }
  public int SHIFT_MASK() { return(Event.SHIFT_MASK);  }

  public int F1()   { return(Event.F1);  }
  public int F2()   { return(Event.F2);  }
  public int F3()   { return(Event.F3);  }
  public int F4()   { return(Event.F4);  }
  public int F5()   { return(Event.F5);  }
  public int F6()   { return(Event.F6);  }
  public int F7()   { return(Event.F7);  }
  public int F8()   { return(Event.F8);  }
  public int F9()   { return(Event.F9);  }
  public int F10()  { return(Event.F10); }
  public int F11()  { return(Event.F11); }
  public int F12()  { return(Event.F12); }

  public int LEFT()     { return(Event.LEFT);    }
  public int RIGHT()    { return(Event.RIGHT);   }
  public int UP()       { return(Event.UP);      }
  public int DOWN()     { return(Event.DOWN);    }
  public int HOME()     { return(Event.HOME);    }
  public int END()      { return(Event.END);     }
  public int PGUP()     { return(Event.PGUP);    }
  public int PGDN()     { return(Event.PGDN);    }

  // constants from java.awt.Font
  public int BOLD()   { return(Font.BOLD);   }
  public int ITALIC() { return(Font.ITALIC); }
  public int PLAIN()  { return(Font.PLAIN);  }


  // constants from java.awt.Frame
  public int CROSSHAIR_CURSOR() { return(Frame.CROSSHAIR_CURSOR);  }
  public int DEFAULT_CURSOR()   { return(Frame.DEFAULT_CURSOR);    }
  public int E_RESIZE_CURSOR()  { return(Frame.E_RESIZE_CURSOR);   }
  public int HAND_CURSOR()      { return(Frame.HAND_CURSOR);       }
  public int MOVE_CURSOR()      { return(Frame.MOVE_CURSOR);       }
  public int NE_RESIZE_CURSOR() { return(Frame.NE_RESIZE_CURSOR);  }
  public int NW_RESIZE_CURSOR() { return(Frame.NW_RESIZE_CURSOR);  }
  public int N_RESIZE_CURSOR()  { return(Frame.N_RESIZE_CURSOR);   }
  public int SE_RESIZE_CURSOR() { return(Frame.SE_RESIZE_CURSOR);  }
  public int SW_RESIZE_CURSOR() { return(Frame.SW_RESIZE_CURSOR);  }
  public int S_RESIZE_CURSOR()  { return(Frame.S_RESIZE_CURSOR);   }
  public int TEXT_CURSOR()      { return(Frame.TEXT_CURSOR);       }
  public int WAIT_CURSOR()      { return(Frame.WAIT_CURSOR);       }
  public int W_RESIZE_CURSOR()  { return(Frame.W_RESIZE_CURSOR);   }


  // constants from java.awt.Label
  public int LABEL_CENTER() { return(Label.CENTER); }
  public int LABEL_LEFT()   { return(Label.LEFT);   }
  public int LABEL_RIGHT()  { return(Label.RIGHT);  }

  // constants from java.awt.ScrollPane
  public int SCROLLBARS_ALWAYS() { return(ScrollPane.SCROLLBARS_ALWAYS);}
  public int SCROLLBARS_AS_NEEDED() { return(ScrollPane.SCROLLBARS_AS_NEEDED);}
  public int SCROLLBARS_NEVER() { return(ScrollPane.SCROLLBARS_NEVER);}


  // constants from java.awt.Scrollbar
  public int SCROLLBAR_HORIZONTAL()   { return(Scrollbar.HORIZONTAL); }
  public int SCROLLBAR_VERTICAL()     { return(Scrollbar.VERTICAL);   }

  // constants from java.awt.FileDialog
  public int LOAD() { return(FileDialog.LOAD); }
  public int SAVE() { return(FileDialog.SAVE); }

  // from java.awt.FlowLayout
  public int FLOWLAYOUT_CENTER() { return(FlowLayout.CENTER); }
  public int FLOWLAYOUT_LEFT()   { return(FlowLayout.LEFT);   }
  public int FLOWLAYOUT_RIGHT()  { return(FlowLayout.RIGHT);  }

  // from java.awt.GridBagConstraints
  public int GRIDBAGCONSTRAINTS_CENTER() 
                                 { return(GridBagConstraints.CENTER);    }
  public int EAST()              { return(GridBagConstraints.EAST);      }
  public int NORTHEAST()         { return(GridBagConstraints.NORTHEAST); }
  public int NORTH()             { return(GridBagConstraints.NORTH);     }
  public int NORTHWEST()         { return(GridBagConstraints.NORTHWEST); }
  public int SOUTH()             { return(GridBagConstraints.SOUTH);     }
  public int SOUTHEAST()         { return(GridBagConstraints.SOUTHEAST); }
  public int SOUTHWEST()         { return(GridBagConstraints.SOUTHWEST);  }
  public int WEST()              { return(GridBagConstraints.WEST);      }
  public int GRIDBAGCONSTRAINTS_HORIZONTAL()  
                                 { return(GridBagConstraints.HORIZONTAL); }
  public int GRIDBAGCONSTRAINTS_VERTICAL()    
                                 { return(GridBagConstraints.VERTICAL);   }
  public int BOTH()              { return(GridBagConstraints.BOTH);      }
  public int NONE()              { return(GridBagConstraints.NONE);      }
  public int RELATIVE()          { return(GridBagConstraints.RELATIVE);  }
  public int REMAINDER()         { return(GridBagConstraints.REMAINDER); }

  // from java.awt.Image
  public Object UndefinedProperty() { return(Image.UndefinedProperty); }

  // from java.awt.MediaTracker
  public int ABORTED()   { return(MediaTracker.ABORTED);  }
  public int COMPLETE()  { return(MediaTracker.COMPLETE); }
  public int ERRORED()   { return(MediaTracker.ERRORED);  }
  public int LOADING()   { return(MediaTracker.LOADING);  }

}
