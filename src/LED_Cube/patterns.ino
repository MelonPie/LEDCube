
bool direct;
unsigned int actualValue;
byte lay, xVal, yVal;
byte place;

void SetLayers(unsigned int value) {
  layer[0] = value; layer[1] = value; layer[2] = value; layer[3] = value;
}

void InversLayers() {
  layer[0] = 65535 - layer[0];
  layer[1] = 65535 - layer[1];
  layer[2] = 65535 - layer[2];
  layer[3] = 65535 - layer[3];
}

void ClearLayers() {
  SetLayers(0);
}

void LayersUpDown() {
  if (start) {
    start = false;
    speed_time = 500;
    direct = true;
  }
  ClearLayers();
  layer[count] = 65535;
  if (direct) {
    count++;
    if (count > 3) {
      direct = false;
      count = 2;
    }
  } else {
    count--; if (count < 1) direct = true;
  }
}

void FallingDot() {
  if (start) {
    start = false; speed_time = 100;
    count = 4;
    actualValue = 1;
    direct = true;
  }
  count--;
  ClearLayers();
  layer[count] = actualValue;
  if (count == 0) {
    count = 4;
    actualValue = actualValue << 1;
    if (actualValue == 0) actualValue = 1;
  }
}

void Rain() {
  if (start) {
    start = false; speed_time = 200;
    ClearLayers();
  }
  layer[0] = layer[1];
  layer[1] = layer[2];
  layer[2] = layer[3];
  layer[3] = 1 << random(16);
}

void Random() {
  if (start) {
    start = false; speed_time = 200;
  }
  layer[0] = random(65536);
  layer[1] = random(65536);
  layer[2] = random(65536);
  layer[3] = random(65536);
}

void AllCube() {
  if (start) {
    start = false; speed_time = 2000;
  }
  ClearLayers();
  switch (count) {
    case 0:
      SetLayers(65535);
      break;
    case 1:
      layer[1] = 1632;
      layer[2] = 1632;
      break;
  }
  count++; if (count > 1) count = 0;
}

void Cut() {
  if (start) {
    start = false; speed_time = 2000;
    layer[0] = 4369;
    layer[1] = 13107;
    layer[2] = 30583;
    layer[3] = 65535;
  }
  InversLayers();
}

void Cube() {
  if (start) {
    start = false; speed_time = 2000;
    layer[0] = 15 + 16 + 128 + 256 + 2048 + 4096 + 8192 + 16384 + 32768;
    layer[1] = 1 + 8 + 4096 + 32768;
    layer[2] = layer[1];
    layer[3] = layer[0];
  }
  InversLayers();
}

void Diagonal() {
  if (start) {
    start = false; speed_time = 2000;
    layer[0] = 33825;
    layer[1] = 33825;
    layer[2] = 33825;
    layer[3] = 33825;
  }
  InversLayers();
}

void Mixer() {
  if (start) {
    start = false; speed_time = 100;
  }
  switch (count) {
    case 0: actualValue = 33825; break;
    case 1: actualValue = 17442; break;
    case 2: actualValue = 8772; break;
    case 3: actualValue = 4680; break;
    case 4: actualValue = 960; break;
    case 5: actualValue = 3120; break;
  }
  SetLayers(actualValue);
  count++;
  if (count > 5) count = 0;
}

void FallingLayer() {
  if (start) {
    start = false; speed_time = 100;
    actualValue = 0;
    direct = false;
  }
  if (actualValue == 0) {
    actualValue = 1;
    ClearLayers();
    direct = !direct;
    layer[3 - (direct ? 0 : 3)] = 65535;
  }
  switch (count) {
    case 0:
      layer[3 - (direct ? 0 : 3)] -= actualValue;
      layer[2 - (direct ? 0 : 1)] = actualValue;
      break;
    case 1:
      layer[1 + (direct ? 0 : 1)] = layer[2  - (direct ? 0 : 1)];
      layer[2 - (direct ? 0 : 1)] = 0;
      break;
    case 2:
      layer[0 + (direct ? 0 : 3)] += layer[1 + (direct ? 0 : 1)];
      layer[1 + (direct ? 0 : 1)] = 0;
      actualValue = actualValue << 1;
      break;
  }
  count++; if (count > 2) count = 0;
}

void LayerCut() {
  if (start) {
    start = false; speed_time = 100;
  }
  if (count) layer[0] = layer[0] << 1;
  else layer[0] = 4369;
  SetLayers(layer[0]);
  count++;
  if (count > 20) count = 0;
}

void Circle() {
  if (start) {
    start = false; speed_time = 100;
    lay = 3;
  }
  switch (count) {
    case 0: ClearLayers(); layer[lay] = 1; break;
    case 1: layer[lay] = 2; break;
    case 2: layer[lay] = 4; break;
    case 3: layer[lay] = 8; break;
    case 4: layer[lay] = 128; break;
    case 5: layer[lay] = 2048; break;
    case 6: layer[lay] = 32768; break;
    case 7: layer[lay] = 16384; break;
    case 8: layer[lay] = 8192; break;
    case 9: layer[lay] = 4096; break;
    case 10: layer[lay] = 256; break;
    case 11: layer[lay] = 16; break;
    case 12: layer[lay] = 1; break;
  }
  count++;
  if (count > 12) {
    count = 0;
    if (lay == 0) lay = 3;
    else lay--;
  }
}

void RandomWay() {
  if (start) {
    start = false; speed_time = 200;
    lay = random(4);
    xVal = random(4);
    yVal = random(4);
  }
  switch (random(7)) {
    case 0: if ((lay + 1) <= 3) lay++; break;
    case 1: if ((lay - 1) >= 0) lay--; break;
    case 2: if ((xVal + 1) <= 3) xVal++; break;
    case 3: if ((xVal - 1) >= 0) xVal--; break;
    case 4: if ((yVal + 1) <= 3) yVal++; break;
    case 5: if ((yVal - 1) >= 0) yVal--; break;
    default: break;
  }
  ClearLayers();
  layer[lay] = (1 << xVal) << (4 * yVal);
}

void SmallCube() {
  if (start) {
    start = false; speed_time = 200;
  }
  switch (count) {
    case 0: lay = random(3); ClearLayers(); actualValue = 51; break;
    case 1: actualValue = actualValue << 1; break;
    case 2: actualValue = actualValue << 1; break;
    case 3: actualValue = actualValue << 4; break;
    case 4: actualValue = actualValue << 4; break;
    case 5: actualValue = actualValue >> 1; break;
    case 6: actualValue = actualValue >> 1; break;
    case 7: actualValue = actualValue >> 4; break;
    case 8: actualValue = actualValue >> 4; break;
  }
  layer[lay] = actualValue;
  layer[lay + 1] = actualValue;
  count++; if (count > 8) count = 0;
}

void RandomWayCube() {
  if (start) {
    start = false; speed_time = 200;
    lay = random(3);
    xVal = random(3);
    yVal = random(3);
  }
  switch (random(7)) {
    case 0: if ((lay + 1) < 3) lay++; break;
    case 1: if ((lay - 1) >= 0) lay--; break;
    case 2: if ((xVal + 1) < 3) xVal++; break;
    case 3: if ((xVal - 1) >= 0) xVal--; break;
    case 4: if ((yVal + 1) < 3) yVal++; break;
    case 5: if ((yVal - 1) >= 0) yVal--; break;
    default: break;
  }
  ClearLayers();
  layer[lay] = (51 << xVal) << (4 * yVal);
  layer[lay + 1] = layer[lay];
}

void GrowingCube() {
  if (start) {
    start = false; speed_time = 1000;
  }
  switch (count) {
    case 0: ClearLayers(); layer[0] = 1; break;
    case 1: layer[0] = 51; layer[1] = 51; break;
    case 2: layer[0] = 1911; layer[1] = 1911; layer[2] = 1911; break;
    case 3: SetLayers(65535); break;
    default: break;
  }
  count++; if (count > 4) count = 0;
}

void FallingLayers() {
  if (start) {
    start = false; speed_time = 200;
    actualValue = 0;
    lay = 4;
  }
  if (actualValue == 0) {
    lay--; if (lay < 1) lay = 3;
    actualValue = 1;
    ClearLayers();
    layer[lay] = 65535;
  }
  layer[lay] -= actualValue;
  layer[lay - 1] += actualValue;
  actualValue = actualValue << 1;
}

void GrowingLine() {
  if (start) {
    start = false; speed_time = 100;
  }
  switch (count) {
    case 0:
      ClearLayers();
      layer[0] = 1;
      lay = 0; xVal = 0; yVal = 0;
      while ((lay == 0) && (xVal == 0) && (yVal == 0)) {
        lay = random(2);
        xVal = random(2);
        yVal = random(2);
      }
      break;
    case 1: layer[lay] += ((xVal == 0) ? 1 : 2) << (4 * yVal); break;
    case 2: layer[2 * lay] += ((xVal == 0) ? 1 : 4) << (8 * yVal); break;
    case 3: layer[3 * lay] += ((xVal == 0) ? 1 : 8) << (12 * yVal); break;
    case 4: layer[3 * lay] -= ((xVal == 0) ? 1 : 8) << (12 * yVal); break;
    case 5: layer[2 * lay] -= ((xVal == 0) ? 1 : 4) << (8 * yVal); break;
    default: break;
  }
  count++; if (count > 5) count = 0;
}

void CircleEdges() {
  if (start) {
    start = false; speed_time = 100;
    lay = 3;
    ClearLayers();
  }
  switch (count) {
    case 0: layer[lay] = 1; break;
    case 1: layer[lay] += 2; break;
    case 2: layer[lay] += 4; break;
    case 3: layer[lay] += 8; break;
    case 4: layer[lay] += 128; break;
    case 5: layer[lay] += 2048; break;
    case 6: layer[lay] += 32768; break;
    case 7: layer[lay] += 16384; break;
    case 8: layer[lay] += 8192; break;
    case 9: layer[lay] += 4096; break;
    case 10: layer[lay] += 256; break;
    case 11: layer[lay] += 16; break;
    default: break;
  }
  count++;
  if (count > 12) {
    count = 0;
    if (lay == 0) {
      lay = 3;
      ClearLayers();
    }
    else lay--;
  }
}

void CircleSide() {
  if (start) {
    start = false; speed_time = 1000;
  }
  switch (count) {
    case 0: SetLayers(15); break;
    case 1: SetLayers(34952); break;
    case 2: SetLayers(61440); break;
    case 3: SetLayers(4369); break;
    case 4: ClearLayers(); layer[0] = 65535; break;
    case 5: SetLayers(34952); break;
    case 6: ClearLayers(); layer[3] = 65535; break;
    case 7: SetLayers(4369); break;
  }
  count++;
  if (count > 7) count = 0;
}

void RandomWayLine() {
  if (start) {
    start = false; speed_time = 200;
    lay = random(3);
    yVal = random(3);
  }
  switch (random(5)) {
    case 0: if ((lay + 1) <= 3) lay++; break;
    case 1: if ((lay - 1) >= 0) lay--; break;
    case 2: if ((yVal + 1) <= 3) yVal++; break;
    case 3: if ((yVal - 1) >= 0) yVal--; break;
    default: break;
  }
  ClearLayers();
  layer[lay] = 15 << (4 * yVal);
}

void RandomWaySide() {
  if (start) {
    start = false; speed_time = 200;
    xVal = random(3);
  }
  switch (random(3)) {
    case 0: if ((xVal + 1) <= 3) xVal++; break;
    case 1: if ((xVal - 1) >= 0) xVal--; break;
    default: break;
  }
  ClearLayers();
  actualValue = 4369 << xVal;
  switch (random(2)) {
    case 0: SetLayers(actualValue); break;
    case 1: layer[1] = actualValue; layer[2] = actualValue; break;
  }
}

void DJCube() {
  if (start) {
    start = false; speed_time = 200;
    xVal = random(3);
  }
  switch (random(3)) {
    case 0: if ((xVal + 1) <= 3) xVal++; break;
    case 1: if ((xVal - 1) >= 0) xVal--; break;
    default: break;
  }
  switch (xVal) {
    case 0: SetLayers(4369); break;
    case 1: SetLayers(13107); break;
    case 2: SetLayers(30583); break;
    case 3: SetLayers(65535); break;
  }
}

void FillingCube() {
  if (start) {
    start = false; speed_time = 200;
    count = 4;
    actualValue = 1;
  }
  if ((count == 4) && (actualValue == 1)) ClearLayers();
  count--;
  layer[count] += actualValue;
  if (count == 0) {
    count = 4;
    actualValue = actualValue << 1;
    if (actualValue == 0) actualValue = 1;
  }
}

void NanoBuilding() {
  if (start) {
    start = false; speed_time = 150;
    actualValue = 0;
    place = 1;
    direct = true;
  }
  if (direct) {
    direct = false;
    while ((actualValue < place) && (place < 64)) {
      lay = random(4);
      xVal = random(4);
      yVal = random(4);
      actualValue = xVal + (yVal * 4) + (lay * 16);
    }
  }
  actualValue = 0;
  int xValP = xVal;
  int yValP = yVal;
  int layP = lay;
  while ((actualValue < place) && (place < 64)) {
    xVal = xValP;
    yVal = yValP;
    lay = layP;
    switch (random(7)) {
      case 0: if ((lay + 1) <= 3) lay++; break;
      case 1: if ((lay - 1) >= 0) lay--; break;
      case 2: if ((xVal + 1) <= 3) xVal++; break;
      case 3: if ((xVal - 1) >= 0) xVal--; break;
      case 4: if ((yVal + 1) <= 3) yVal++; break;
      case 5: if ((yVal - 1) >= 0) yVal--; break;
      default: break;
    }
    actualValue = xVal + (yVal * 4) + (lay * 16);
  }
  if (actualValue == place) {
    place++;
    direct = true;
  }
  ClearLayers();
  if (place < 16) layer[0] = (1 << place) - 1;
  else {
    if (place < 32) {
      layer[1] = (1 << (place - 16)) - 1;
      layer[0] = 65535;
    } else {
      if (place < 48) {
        layer[2] = (1 << (place - 32)) - 1;
        layer[0] = 65535;
        layer[1] = 65535;
      } else {
        if (place < 64) {
          SetLayers(65535);
          layer[3] = (1 << (place - 48)) - 1;
        } else place = 1;
      }
    }
  }
  layer[lay] |= ((1 << xVal) << (4 * yVal));
}

void Curve() {
  int line[4] = {4369, 8738, 17476, 34952};
  byte pos[12] = {0, 1, 2, 3, 3, 2, 1, 0, 0, 1, 2, 3};

  if (start) {
    start = false; speed_time = 100;
  }
  layer[0] = ((pos[count] == 0) ? line[0] : 0) + ((pos[count + 1] == 0) ? line[1] : 0) + ((pos[count + 2] == 0) ? line[2] : 0) + ((pos[count + 3] == 0) ? line[3] : 0);
  layer[1] = ((pos[count] == 1) ? line[0] : 0) + ((pos[count + 1] == 1) ? line[1] : 0) + ((pos[count + 2] == 1) ? line[2] : 0) + ((pos[count + 3] == 1) ? line[3] : 0);
  layer[2] = ((pos[count] == 2) ? line[0] : 0) + ((pos[count + 1] == 2) ? line[1] : 0) + ((pos[count + 2] == 2) ? line[2] : 0) + ((pos[count + 3] == 2) ? line[3] : 0);
  layer[3] = ((pos[count] == 3) ? line[0] : 0) + ((pos[count + 1] == 3) ? line[1] : 0) + ((pos[count + 2] == 3) ? line[2] : 0) + ((pos[count + 3] == 3) ? line[3] : 0);
  count++; if (count > 7) count = 0;
}

struct snake {
  byte x, y, z;
} obj[7];

void Snake() {
  int k;
  byte c = 7;
  if (start) {
    start = false; speed_time = 200;
    for (k = 0; k < c; k++) {
      obj[k].x = 0;
      obj[k].y = 0;
      obj[k].z = 0;
    }
    lay = 0;
    xVal = 0;
    yVal = 0;
  }
  int xValP = xVal;
  int yValP = yVal;
  int layP = lay;
  direct = true;
  while (direct) {
    xVal = xValP;
    yVal = yValP;
    lay = layP;
    switch (random(6)) {
      case 0: if ((lay + 1) <= 3) lay++; break;
      case 1: if ((lay - 1) >= 0) lay--; break;
      case 2: if ((xVal + 1) <= 3) xVal++; break;
      case 3: if ((xVal - 1) >= 0) xVal--; break;
      case 4: if ((yVal + 1) <= 3) yVal++; break;
      case 5: if ((yVal - 1) >= 0) yVal--; break;
      default: break;
    }
    direct = false;
    for (k = 0; k < c; k++) {
      if ((xVal == obj[k].x) && (yVal == obj[k].y) && (lay == obj[k].z)) direct = true;
    }
  }
  for (k = c - 2; k >= 0; k--) {
    obj[k + 1].x = obj[k].x;
    obj[k + 1].y = obj[k].y;
    obj[k + 1].z = obj[k].z;
  }
  obj[0].x = xVal;
  obj[0].y = yVal;
  obj[0].z = lay;
  ClearLayers();
  for (k = 0; k < c; k++) {
    layer[obj[k].z] += (1 << obj[k].x) << (4 * obj[k].y);
  }
}

void BDay() {
/*
# Short notes to build the letters
# H = 44714
# A = 44718
# P = 36012
# Y = 20138
# B = 60140
# D = 51884
# L = 59528
# E = 60558
# X = 42154
*/
  int letters[16] = {44714, 44718, 36012, 36012, 20138, 0, 60140, 51884, 44718, 20138, 0, 44718, 59528, 60558, 42154, 0};
  if (start) {
    start = false; speed_time = 1000;
    ClearLayers();
  }
  for(int past=3; past>=0; past--){
    if((count-past) >= 0) {
      layer[3-past] = letters[count-past];
    } else {
      layer[3-past] = 0;
    }
  }

  //layer[3] = letters[count];
  count++;
  if (count == 16) count = 0;
}
