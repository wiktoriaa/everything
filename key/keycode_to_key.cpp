#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

string intToString(int x)
{
  string tmp;
  sprintf((char*)tmp.c_str(), "%d", x);
  string str = tmp.c_str();
  return str;
}

int main(int argc, char const *argv[]) {
  fstream file_in;
  int c;
  string out;
  if (argc == 3) {
    file_in.open(argv[1]);
    ofstream file_out(argv[2]);
    while (file_in >> c) {

      if(c){
           out = "";
           if(c == 1)
             out = "[LMOUSE]"; 
           else if(c == 2)
             out = "[RMOUSE]";
           else if(c == 4)
             out = "[MMOUSE]";
           else if(c == 13)
             out = "[RETURN]";
           else if(c == 16 || c == 17 || c == 18)
             out = "";
           else if(c == 160 || c == 161)
             out = "[SHIFT]";
           else if(c == 162 || c == 163)
             out = "[STRG]";
           else if(c == 164)
             out = "[ALT]";
           else if(c == 165)
             out = "[ALT GR]";
           else if(c == 8)
             out = "[BACKSPACE]";
           else if(c == 9)
             out = "[TAB]";
           else if(c == 27)
             out = "[ESC]";
           else if(c == 33)
             out = "[PAGE UP]";
           else if(c == 34)
             out = "[PAGE DOWN]";
           else if(c == 35)
             out = "[HOME]";
           else if(c == 36)
             out = "[POS1]";
           else if(c == 37)
             out = "[ARROW LEFT]";
           else if(c == 38)
             out = "[ARROW UP]";
           else if(c == 39)
             out = "[ARROW RIGHT]";
           else if(c == 40)
             out = "[ARROW DOWN]";
           else if(c == 45)
             out = "[INS]";
           else if(c == 46)
             out = "[DEL]";
           else if(c >= 65 && c <= 90 || c >= 48 && c <= 57 || c == 32)
             out = c;

           else if(c == 91 || c == 92)
             out = "[WIN]";
           else if(c >= 96 && c <= 105)
             out = "[NUM " + intToString(c - 96) + "]";
           else if(c == 106)
             out = "[NUM /]";
           else if(c == 107)
             out = "[NUM +]";
           else if(c == 109)
             out = "[NUM -]";
           else if(c == 109)
             out = "[NUM ,]";
           else if(c >= 112 && c <= 123)
             out = "[F" + intToString(c - 111) + "]";
           else if(c == 144)
             out = "[NUM]";
           else if(c == 192)
             out = "[OE]";
           else if(c == 222)
             out = "[AE]";
           else if(c == 186)
             out = "[UE]";
           else if(c == 186)
             out = "+";
           else if(c == 188)
             out = ",";
           else if(c == 189)
             out = "-";
           else if(c == 190)
             out = ".";
           else if(c == 191)
             out = "#";
           else if(c == 226)
             out = "<";

           else
             out = "[KEY \\" + intToString(c) + "]";
        }
        file_out << out;
      }
  }
  else
    cout << "Usage: " << argv[0] << " <input file> <output file>" << endl;
  return 0;
}
