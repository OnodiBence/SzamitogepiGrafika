#include <stdio.h>

// Color struktúra RGB komponensekkel
typedef struct {
    int red;
    int green;
    int blue;
} Color;

// Line struktúra szakasz végpontjaival és színével
typedef struct {
    int x1, y1; // Kezdőpont koordinátái
    int x2, y2; // Végpont koordinátái
    Color color; // Szín
} Line;

int main() {
    // Példa egy Line struktúra létrehozására és inicializálására
    Line line1 = {0, 0, 100, 100, {255, 0, 0}}; // Piros színű szakasz az (0,0) és (100,100) pontok között
    
    // Kiírás ellenőrzés céljából
    printf("Kezdopont: (%d, %d)\n", line1.x1, line1.y1);
    printf("Vegpont: (%d, %d)\n", line1.x2, line1.y2);
    printf("Szin: RGB(%d, %d, %d)\n", line1.color.red, line1.color.green, line1.color.blue);

    return 0;
}