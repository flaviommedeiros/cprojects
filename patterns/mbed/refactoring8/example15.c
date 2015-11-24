class AnalogOut {

public:

    /** Create an AnalogOut connected to the specified pin
     *
     *  @param AnalogOut pin to connect to (18)
     */
    AnalogOut(PinName pin) {
        analogout_init(&_dac, pin);
    }

    /** Set the output voltage, specified as a percentage (float)
     *
     *  @param value A floating-point value representing the output voltage,
     *    specified as a percentage. The value should lie between
     *    0.0f (representing 0v / 0%) and 1.0f (representing 3.3v / 100%).
     *    Values outside this range will be saturated to 0.0f or 1.0f.
     */
    void write(float value) {
        analogout_write(&_dac, value);
    }

    /** Set the output voltage, represented as an unsigned short in the range [0x0, 0xFFFF]
     *
     *  @param value 16-bit unsigned short representing the output voltage,
     *            normalised to a 16-bit value (0x0000 = 0v, 0xFFFF = 3.3v)
     */
    void write_u16(unsigned short value) {
        analogout_write_u16(&_dac, value);
    }

    /** Return the current output voltage setting, measured as a percentage (float)
     *
     *  @returns
     *    A floating-point value representing the current voltage being output on the pin,
     *    measured as a percentage. The returned value will lie between
     *    0.0f (representing 0v / 0%) and 1.0f (representing 3.3v / 100%).
     *
     *  @note
     *    This value may not match exactly the value set by a previous write().
     */
    float read() {
        return analogout_read(&_dac);
    }

#ifdef MBED_OPERATORS
    /** An operator shorthand for write()
     */
    AnalogOut& operator= (float percent) {
        write(percent);
        return *this;
    }

    AnalogOut& operator= (AnalogOut& rhs) {
        write(rhs.read());
        return *this;
    }

    /** An operator shorthand for read()
     */
    operator float() {
        return read();
    }
#endif

protected:
    dac_t _dac;
}
