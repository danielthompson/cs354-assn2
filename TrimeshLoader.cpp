//
// Created by Daniel Thompson on 4/26/16.
//

#include "TrimeshLoader.h"

TokenPair *TrimeshLoader::tokenMatch(char *srchtok) {
   if (!srchtok)
      return 0;
   TokenPair *ptokp = &tokenMap[0];
   for (; *ptokp != EMPTY_PAIR && strcmp(ptokp->strval, srchtok) != 0; ptokp++);
   if (*ptokp == EMPTY_PAIR) ptokp = 0;
   return ptokp;
}

TokenPair TrimeshLoader::EMPTY_PAIR = {"", T_NONE};

char TrimeshLoader::TOK_SEPS[] = " \t";

void TrimeshLoader::loadOBJ(const char *objfile, Trimesh *pmesh) {
   std::ifstream ifs;
   char line[LINE_SIZE];
   char *tok;
   ifs.open(objfile);
   while (!ifs.eof()) {
      ifs.getline(line, LINE_SIZE);
      tok = strtok(line, TOK_SEPS);
      TokenPair *ptokp = tokenMatch(tok);
      if (ptokp) {
         switch (ptokp->tokID) {
            case T_VERT    :
               processVertex(tok, pmesh);
               break;
            case T_FACE    :
               processFace(tok, pmesh);
               break;
            default:
               processSkip(tok);
               break;
         }
      }
   }
   ifs.close();
}

TokenPair TrimeshLoader::tokenMap[] = {
      {"v", T_VERT}, {"f", T_FACE},
      EMPTY_PAIR
};

int TrimeshLoader::readFloats(char *tok, float *buf, int bufsz) {
   int i = 0;
   while ((tok = strtok(0, TOK_SEPS)) != 0 && i < bufsz)
      buf[i++] = atof(tok);
   return i;
}

int TrimeshLoader::readInts(char *tok, int *buf, int bufsz) {
   int i = 0;
   while ((tok = strtok(0, TOK_SEPS)) != 0 && i < bufsz)
      buf[i++] = atoi(tok);
   return i;
}

void TrimeshLoader::processVertex(char *tok, Trimesh *pmsh) {
   float values[3];
   int cnt = readFloats(tok, values, 3);
   if (cnt >= 3) pmsh->addVertex(values);
}

bool TrimeshLoader::processFace(char *tok, Trimesh *pmsh) {
   int ids[256];
   int cnt = readInts(tok, ids, 256);
   if (cnt >= 3) {
      int tri[3] = {ids[0] - 1, ids[1] - 1, ids[2] - 1};
      pmsh->addFace(tri);
      for (int i = 3; i < cnt; i++) {
         tri[1] = tri[2];
         tri[2] = ids[i] - 1;
         pmsh->addFace(tri);
      }
   }

   return true;
}