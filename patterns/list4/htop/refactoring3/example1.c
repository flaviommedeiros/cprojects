switch (key) {
   case KEY_DOWN:
   case KEY_CTRLN:
      this->selected++;
      break;
   case KEY_UP:
   case KEY_CTRLP:
      this->selected--;
      break;
   #ifdef KEY_C_DOWN
   case KEY_C_DOWN:
      this->selected++;
      break;
   #endif
   #ifdef KEY_C_UP
   case KEY_C_UP:
      this->selected--;
      break;
   #endif
   case KEY_LEFT:
   case KEY_CTRLB:
      if (this->scrollH > 0) {
         this->scrollH -= CRT_scrollHAmount;
         this->needsRedraw = true;
      }
      break;
   case KEY_RIGHT:
   case KEY_CTRLF:
      this->scrollH += CRT_scrollHAmount;
      this->needsRedraw = true;
      break;
   case KEY_PPAGE:
      this->selected -= (this->h - 1);
      this->scrollV -= (this->h - 1);
      this->needsRedraw = true;
      break;
   case KEY_NPAGE:
      this->selected += (this->h - 1);
      this->scrollV += (this->h - 1);
      this->needsRedraw = true;
      break;
   case KEY_WHEELUP:
      this->selected -= CRT_scrollWheelVAmount;
      this->scrollV -= CRT_scrollWheelVAmount;
      this->needsRedraw = true;
      break;
   case KEY_WHEELDOWN:
   {
      this->selected += CRT_scrollWheelVAmount;
      this->scrollV += CRT_scrollWheelVAmount;
      if (this->scrollV > Vector_size(this->items) - this->h) {
         this->scrollV = Vector_size(this->items) - this->h;
      }
      this->needsRedraw = true;
      break;
   }
   case KEY_HOME:
      this->selected = 0;
      break;
   case KEY_END:
      this->selected = size - 1;
      break;
   default:
      return false;
   }
