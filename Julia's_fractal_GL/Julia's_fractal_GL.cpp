#include <iostream>
#include "GLFW/glfw3.h"
double zoom=0.5, xMove=0, yMove=0;
void Draw(int w,int h, double cRe, double cIm,int n,int radius)
{
    double Re1, Re2, Im1, Im2;
    for (int i = 0; i < w; i++)
    {
        for (int j = 0; j < h; j++)
        {
            Re1 = (i - w/2 ) / (zoom * w) + xMove;
            Im1 = (j - h/2 ) / (zoom * h) + yMove;
            long k;
            for (k = 0; k < n; k++)
            {
                Re2 = Re1;
                Im2 = Im1;
                //z = z^-2 + c:
                //Im1 = (Re2 * Re2 + Im2 * Im2) / ((Re2 * Re2 - Im2 * Im2) * (Re2 * Re2 - Im2 * Im2)) + cRe;
                //Re1 = (-2 * Im2 * Re2) / ((Re2 * Re2 - Im2 * Im2) * (Re2 * Re2 - Im2 * Im2)) + cIm;
                //z = z^-1 + c:
                //Re1 = Re2 / (Re2 * Re2 - Im2 * Im2) + cRe;
                //Im1 = -Im2 / (Re2 * Re2 - Im2 * Im2) + cIm;
                //z = z^1 + c:
                //Re1 = Re2 + cRe;
                //Im1 = Im2 + cIm;
                //z = z^2 + c:
                //Re1 = Re2 * Re2 - Im2 * Im2 + cRe;
                //Im1 = 2 * Re2 * Im2 + cIm;
                //z = z^3 + c:
                Re1 = Re2 * Re2 * Re2 - 3 * Re2 * Im2 * Im2 + cRe;
                Im1 = 3 * Re2 * Re2 * Im2 - Im2 * Im2 * Im2 + cIm;
                //z = z^4 + c:
                //Re1 = Re2 * Re2 * Re2 * Re2 - Re2 * Re2 * Im2 * Im2 + Im2 * Im2 * Im2 * Im2 + cRe;
                //Im1 = Re2 * Re2 * Re2 * Im2 - Re2 * Im2 * Im2 * Im2 + cIm;
                //z = z^5 + c:
                //Re1 = Re2 * Re2 * Re2 * Re2 * Re2 - 10 * Re2 * Re2 * Re2 * Im2 * Im2 + 5 * Re2 * Im2 * Im2 * Im2 * Im2 + cRe;
                //Im1 = 5 * Re2 * Re2 * Re2 * Re2 * Im2 - 10 * Im2 * Im2 * Im2 * Re2 * Re2 - Im2 * Im2 * Im2 * Im2 * Im2 + cIm;

                if (Re1 * Re1 + Im1 * Im1 > radius)
                    break;
            }
            //b.SetPixel(i, j, Color.FromArgb(255, (int)((k * 10) % 255), (int)((k * 5) % 255), (int)((k * 2) % 255)));
            glColor3d((double)((k * 10) % 255) / 255, (double)((k * 5) % 255) / 255, (double)((k * 2) % 255) / 255);
            glVertex2d((double)i*2 / (double)w-1, (double)j*2 / (double)h-1);
        }
    }
}
int main()
{
    if (!glfwInit())
        return -1;
    int w = 500, h = 500;
    double cRe, cIm;
    long n = 200;// Convert.ToInt64(textBox1.Text);
    int radius = 10;// trackBar3.Value;
    //
    cRe = -0.6415;// (double)trackBar1.Value / 10000;
    cIm = 0.4697;// (double)trackBar2.Value / 10000;
    GLFWwindow* window;
    window = glfwCreateWindow(w, h, "", NULL/*glfwGetPrimaryMonitor()*/, NULL);
    glfwMakeContextCurrent(window);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    int statR, statL, statD, statU, statQ, statE, statZ, statN, statRad;
    std::cout << "\na,w,s,d - is for moving";
    std::cout << "\nq+w or q+s - is for changing first parameter";
    std::cout << "\ne+w or e+s - is for changing second parameter";
    std::cout << "\nz+w or z+s - is for zooming in/out";
    std::cout << "\nr+w or r+s - is for changing radius";
    std::cout << "\nn+w or n+s - is for changing number of iteration";
    //std::cout << "";
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0, 0, 0, 1);
    glBegin(GL_POINTS);
    Draw(w, h, cRe, cIm, n, radius);
    glEnd();
    glfwSwapBuffers(window);
    glfwPollEvents();
    while (!glfwWindowShouldClose(window))
    {
        statR = glfwGetKey(window, GLFW_KEY_D);
        statL = glfwGetKey(window, GLFW_KEY_A);
        statU = glfwGetKey(window, GLFW_KEY_W);
        statD = glfwGetKey(window, GLFW_KEY_S);
        statQ = glfwGetKey(window, GLFW_KEY_Q);
        statE = glfwGetKey(window, GLFW_KEY_E);
        statZ = glfwGetKey(window, GLFW_KEY_Z);
        statN = glfwGetKey(window, GLFW_KEY_N);
        statRad = glfwGetKey(window, GLFW_KEY_R);

        if (statR || statL || statU || statD || statQ || statE || statZ)
        {
            if (statR)xMove += 1 / (zoom * 50);
            if (statL)xMove -= 1 / (zoom * 50);
            if (statU && statQ)cRe += 0.001;
            else if (statU && statE)cIm += 0.001;
            else if (statU && statZ)zoom += zoom / 50;
            else if (statU && statN)n += 1;
            else if (statU && statRad)radius += 1;
            else if (statU)yMove += 1 / (zoom * 50);
            if (statD && statQ)cRe -= 0.001;
            else if (statD && statE)cIm -= 0.001;
            else if (statD && statZ)zoom -= zoom / 50;
            else if (statD && statN)n -= 1;
            else if (statD && statRad)radius -= 1;
            else if (statD)yMove -= 1 / (zoom * 50);
            glClear(GL_COLOR_BUFFER_BIT);
            glClearColor(0, 0, 0, 1);
            glBegin(GL_POINTS);
            Draw(w, h, cRe, cIm, n, radius);
            glEnd();
        glfwSwapBuffers(window);
        }
        glfwPollEvents();

    }
}