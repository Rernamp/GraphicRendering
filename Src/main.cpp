#include <iostream>

#include <tgaimage.h>
#include <DrawUtils.h>

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);
const TGAColor green   = TGAColor(0, 255,   0,   255);

int main(int argc, char** argv) {
	if (argc != 2) {
		return -1;
	}
	TGAImage image(300, 300, TGAImage::RGB);

	Utils::line(0, 0, 10, 10, image, red);

	Vector2 t0[3] = {Vector2(10, 70),   Vector2(50, 160),  Vector2(70, 80)};
    Vector2 t1[3] = {Vector2(180, 50),  Vector2(150, 1),   Vector2(70, 180)};
    Vector2 t2[3] = {Vector2(180, 150), Vector2(120, 160), Vector2(130, 180)};


    Utils::triangle(t0[0], t0[1], t0[2], image, red);
    Utils::triangle(t1[0], t1[1], t1[2], image, white);
    Utils::triangle(t2[0], t2[1], t2[2], image, green);

	image.write_tga_file(argv[1]);
	
    return 0;
}