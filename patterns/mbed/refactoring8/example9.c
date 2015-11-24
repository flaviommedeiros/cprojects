class BusIn {

public:
    /* Group: Configuration Methods */

    /** Create an BusIn, connected to the specified pins
     *
     * @param <n> DigitalIn pin to connect to bus bit <n> (p5-p30, NC)
     *
     * @note
     *  It is only required to specify as many pin variables as is required
     *  for the bus; the rest will default to NC (not connected)
     */
    BusIn(PinName p0, PinName p1 = NC, PinName p2 = NC, PinName p3 = NC,
          PinName p4 = NC, PinName p5 = NC, PinName p6 = NC, PinName p7 = NC,
          PinName p8 = NC, PinName p9 = NC, PinName p10 = NC, PinName p11 = NC,
          PinName p12 = NC, PinName p13 = NC, PinName p14 = NC, PinName p15 = NC);

    BusIn(PinName pins[16]);

    virtual ~BusIn();

    /** Read the value of the input bus
     *
     *  @returns
     *   An integer with each bit corresponding to the value read from the associated DigitalIn pin
     */
    int read();

    /** Set the input pin mode
     *
     *  @param mode PullUp, PullDown, PullNone
     */
    void mode(PinMode pull);

    /** Binary mask of bus pins connected to actual pins (not NC pins)
     *  If bus pin is in NC state make corresponding bit will be cleared (set to 0), else bit will be set to 1
     *
     *  @returns
     *    Binary mask of connected pins
     */
    int mask() {
        return _nc_mask;
    }

#ifdef MBED_OPERATORS
    /** A shorthand for read()
     */
    operator int();

    /** Access to particular bit in random-iterator fashion
     */
    DigitalIn & operator[] (int index);
#endif

protected:
    DigitalIn* _pin[16];

    /** Mask of bus's NC pins
     * If bit[n] is set to 1 - pin is connected
     * if bit[n] is cleared - pin is not connected (NC)
     */
    int _nc_mask;

    /* disallow copy constructor and assignment operators */
private:
    BusIn(const BusIn&);
    BusIn & operator = (const BusIn&);
}
