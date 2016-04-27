#ifndef __LOADER_H__
#define __LOADER_H__

#include <iostream>
#include <fstream>
#include <cstring>
#include "Trimesh.h"

#define LINE_SIZE    1024
#define TOKEN_LENGTH 8

enum TokenID {
   T_NONE = -1, T_VERT, T_FACE
};

struct TokenPair {
   char strval[TOKEN_LENGTH];
   TokenID tokID;

   bool operator==(const TokenPair &rhs) const {
      return strcmp(strval, rhs.strval) == 0 && tokID == rhs.tokID;
   }

   bool operator!=(const TokenPair &rhs) const {
      return !(*this == rhs);
   }
};

class TrimeshLoader {
public:

   static TokenPair EMPTY_PAIR;
   static TokenPair tokenMap[];
   static char TOK_SEPS[];

   TokenPair * tokenMatch(char *srchtok);
   void loadOBJ(const char *objfile, Trimesh *pmesh);
   int readFloats(char *tok, float *buf, int bufsz);
   int readInts(char *tok, int *buf, int bufsz);
   void processSkip(char *tok) { }
   void processVertex(char *tok, Trimesh *pmsh);
   bool processFace(char *tok, Trimesh *pmsh);
};




#endif
