static const char *fragment_shader[] = {
   "#ifdef GL_ES\n",
   "precision mediump float;\n",
   "#endif\n",
   "varying vec4 color;",
   "void main() {",
   "  gl_FragColor = color;",
   "}",
};
