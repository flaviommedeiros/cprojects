class Print
{
  private:
    void printNumber(unsigned long, uint8_t);
    void printFloat(double, uint8_t);
  public:
     
    //
    // Drakelive  2012-09-04
    //
    #if ARDUINO >= 100 
        virtual size_t write(uint8_t) = 0;
    #else
        virtual void write(uint8_t) = 0;
    #endif
     
    // Drakelive  2012-09-04     

    virtual void write(const char *str);
    virtual void write(const uint8_t *buffer, size_t size);
    
    void print(const String &);
    void print(const char[]);
    void print(char, int = BYTE);
    void print(unsigned char, int = BYTE);
    void print(int, int = DEC);
    void print(unsigned int, int = DEC);
    void print(long, int = DEC);
    void print(unsigned long, int = DEC);
    void print(double, int = 2);

    void println(const String &s);
    void println(const char[]);
    void println(char, int = BYTE);
    void println(unsigned char, int = BYTE);
    void println(int, int = DEC);
    void println(unsigned int, int = DEC);
    void println(long, int = DEC);
    void println(unsigned long, int = DEC);
    void println(double, int = 2);
    void println(void);
}
