namespace mbed {

/** A digital output bus, used for setting the state of a collection of pins
 */
class BusOut {

public:

    /** Create an BusOut, connected to the specified pins
     *
     *  @param p<n> DigitalOut pin to connect to bus bit <n> (p5-p30, NC)
     *
     *  @note
     *  It is only required to specify as many pin variables as is required
     *  for the bus; the rest will default to NC (not connected)
     */
    BusOut(PinName p0, PinName p1 = NC, PinName p2 = NC, PinName p3 = NC,
           PinName p4 = NC, PinName p5 = NC, PinName p6 = NC, PinName p7 = NC,
           PinName p8 = NC, PinName p9 = NC, PinName p10 = NC, PinName p11 = NC,
           PinName p12 = NC, PinName p13 = NC, PinName p14 = NC, PinName p15 = NC);

    BusOut(PinName pins[16]);

    virtual ~BusOut();

    /** Write the value to the output bus
     *
     *  @param value An integer specifying a bit to write for every corresponding DigitalOut pin
     */
    void write(int value);

    /** Read the value currently output on the bus
     *
     *  @returns
     *    An integer with each bit corresponding to associated DigitalOut pin setting
     */
    int read();

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
    /** A shorthand for write()
     */
    BusOut& operator= (int v);
    BusOut& operator= (BusOut& rhs);

    /** Access to particular bit in random-iterator fashion
     */
    DigitalOut& operator[] (int index);

    /** A shorthand for read()
     */
    operator int();
#endif

protected:
    DigitalOut* _pin[16];

    /** Mask of bus's NC pins
     * If bit[n] is set to 1 - pin is connected
     * if bit[n] is cleared - pin is not connected (NC)
     */
    int _nc_mask;

   /* disallow copy constructor and assignment operators */
private:
    BusOut(const BusOut&);
    BusOut & operator = (const BusOut&);
};

}
