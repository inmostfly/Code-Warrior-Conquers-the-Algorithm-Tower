#include <graphics.h>
#include <easyx.h>

// 绘制支持透明通道的图像（可切片）
// img:     源图（必须是带透明通道的 PNG）
// x, y:    绘制位置
// w, h:    绘制的宽高（从源图裁剪的大小）
// sx, sy:  从源图的哪个位置开始裁剪
void putimage_alpha_clip( int x, int y, int w, int h,IMAGE* img ,int sx, int sy) {
    // 先绘制到内存DC（带Alpha通道）
    DWORD* src = GetImageBuffer(img);
    DWORD* dst = GetImageBuffer();
    int imgW = img->getwidth();
    int imgH = img->getheight();
    int winW = getwidth();
    int winH = getheight();

    for (int iy = 0; iy < h; iy++) {
        int dy = y + iy;
        if (dy < 0 || dy >= winH) continue;

        for (int ix = 0; ix < w; ix++) {
            int dx = x + ix;
            if (dx < 0 || dx >= winW) continue;

            DWORD sc = src[(sy + iy) * imgW + (sx + ix)];
            unsigned char alpha = (sc >> 24) & 0xFF;
            if (alpha == 0) continue; // 完全透明，直接跳过

            if (alpha == 255) {
                dst[dy * winW + dx] = sc; // 不透明，直接覆盖
            }
            else {
                // 半透明混合
                DWORD dc = dst[dy * winW + dx];
                unsigned char sr = (sc >> 16) & 0xFF;
                unsigned char sg = (sc >> 8) & 0xFF;
                unsigned char sb = sc & 0xFF;
                unsigned char dr = (dc >> 16) & 0xFF;
                unsigned char dg = (dc >> 8) & 0xFF;
                unsigned char db = dc & 0xFF;

                unsigned char rr = (sr * alpha + dr * (255 - alpha)) / 255;
                unsigned char rg = (sg * alpha + dg * (255 - alpha)) / 255;
                unsigned char rb = (sb * alpha + db * (255 - alpha)) / 255;

                dst[dy * winW + dx] = (0xFF << 24) | (rr << 16) | (rg << 8) | rb;
            }
        }
    }
}
