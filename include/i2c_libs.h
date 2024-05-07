
class I2C_Libs{
    public:
    void i2c_init();
    void i2c_stop();
    void i2c_start();
    unsigned char i2c_read(unsigned char isLast);
    void i2c_write(unsigned char data);
};
