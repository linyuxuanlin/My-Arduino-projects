const uint8_t unknown[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x7F, 0x00, 0x00, 0x00, 0x70, 0x80, 0x03, 0x00, 0x00,
                            0x0C, 0x00, 0x0C, 0x00, 0x00, 0x03, 0x00, 0x30, 0x00, 0x80, 0x01, 0x00, 0x40, 0x00, 0x40, 0x00,
                            0x00, 0x80, 0x00, 0x20, 0x00, 0x00, 0x00, 0x01, 0x10, 0x00, 0x00, 0x00, 0x02, 0x10, 0x00, 0x00,
                            0x00, 0x06, 0x08, 0x00, 0x00, 0x00, 0x04, 0x0C, 0x00, 0x0C, 0x00, 0x08, 0x04, 0x00, 0x73, 0x00,
                            0x08, 0x04, 0x80, 0x80, 0x00, 0x18, 0x02, 0x40, 0x80, 0x01, 0x10, 0x02, 0x40, 0x00, 0x01, 0x10,
                            0x02, 0x00, 0x00, 0x01, 0x10, 0x02, 0x00, 0x80, 0x01, 0x10, 0x02, 0x00, 0xC0, 0x00, 0x20, 0x02,
                            0x00, 0x60, 0x00, 0x20, 0x02, 0x00, 0x18, 0x00, 0x20, 0x02, 0x00, 0x08, 0x00, 0x10, 0x02, 0x00,
                            0x08, 0x00, 0x10, 0x02, 0x00, 0x08, 0x00, 0x10, 0x02, 0x00, 0x00, 0x00, 0x10, 0x04, 0x00, 0x00,
                            0x00, 0x18, 0x04, 0x00, 0x00, 0x00, 0x08, 0x0C, 0x00, 0x08, 0x00, 0x08, 0x08, 0x00, 0x00, 0x00,
                            0x04, 0x10, 0x00, 0x00, 0x00, 0x06, 0x30, 0x00, 0x00, 0x00, 0x02, 0x20, 0x00, 0x00, 0x00, 0x01,
                            0x40, 0x00, 0x00, 0x80, 0x00, 0x80, 0x01, 0x00, 0x60, 0x00, 0x00, 0x03, 0x00, 0x30, 0x00, 0x00,
                            0x0C, 0x00, 0x0C, 0x00, 0x00, 0x70, 0x80, 0x03, 0x00, 0x00, 0x80, 0x7F, 0x00, 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

const uint8_t sunny[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00,
                          0x00, 0x08, 0x00, 0x00, 0x00, 0x04, 0x08, 0x10, 0x00, 0x00, 0x08, 0x00, 0x08, 0x00, 0x00, 0x10,
                          0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x00, 0x00, 0x00, 0xC0, 0x80,
                          0x01, 0x00, 0x10, 0x30, 0x00, 0x06, 0x04, 0x20, 0x18, 0x00, 0x0C, 0x02, 0x40, 0x0C, 0x00, 0x18,
                          0x01, 0x00, 0x04, 0x00, 0x10, 0x00, 0x00, 0x02, 0x00, 0x20, 0x00, 0x00, 0x02, 0x00, 0x20, 0x00,
                          0x00, 0x01, 0x00, 0x40, 0x00, 0x00, 0x01, 0x00, 0x40, 0x00, 0x00, 0x01, 0x00, 0x40, 0x00, 0x1E,
                          0x01, 0x00, 0x40, 0x3C, 0x00, 0x01, 0x00, 0x40, 0x00, 0x00, 0x01, 0x00, 0x40, 0x00, 0x00, 0x01,
                          0x00, 0x40, 0x00, 0x00, 0x02, 0x00, 0x20, 0x00, 0x00, 0x02, 0x00, 0x20, 0x00, 0x00, 0x04, 0x00,
                          0x10, 0x00, 0x40, 0x0C, 0x00, 0x18, 0x01, 0x20, 0x18, 0x00, 0x0C, 0x02, 0x10, 0x30, 0x00, 0x06,
                          0x04, 0x00, 0xC0, 0x80, 0x01, 0x00, 0x00, 0x00, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                          0x00, 0x10, 0x00, 0x04, 0x00, 0x00, 0x08, 0x00, 0x08, 0x00, 0x00, 0x04, 0x08, 0x10, 0x00, 0x00,
                          0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00,
                          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

const uint8_t overcast[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00,
                             0x00, 0x08, 0x00, 0x00, 0x00, 0x04, 0x08, 0x10, 0x00, 0x00, 0x08, 0x00, 0x08, 0x00, 0x00, 0x08,
                             0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x00, 0x00, 0x00, 0xC0, 0x80,
                             0x01, 0x00, 0x10, 0x30, 0x00, 0x06, 0x04, 0x20, 0x18, 0x00, 0x0C, 0x02, 0x40, 0x0C, 0x00, 0x18,
                             0x01, 0x00, 0x04, 0x00, 0x10, 0x00, 0x00, 0x02, 0x00, 0x20, 0x00, 0x00, 0x02, 0x00, 0x20, 0x00,
                             0x00, 0x01, 0x00, 0x60, 0x00, 0x00, 0x01, 0x00, 0x40, 0x00, 0x00, 0x01, 0x00, 0x40, 0x00, 0x1E,
                             0x01, 0x07, 0x40, 0x3C, 0x00, 0xE1, 0x38, 0x40, 0x00, 0x00, 0x18, 0x40, 0x40, 0x00, 0x00, 0x0C,
                             0x80, 0x00, 0x00, 0x00, 0x04, 0x00, 0x01, 0x00, 0xC0, 0x03, 0x00, 0x1F, 0x00, 0x30, 0x00, 0x00,
                             0x60, 0x00, 0x0C, 0x00, 0x00, 0x80, 0x01, 0x04, 0x00, 0x00, 0x00, 0x01, 0x02, 0x00, 0x00, 0x00,
                             0x02, 0x02, 0x00, 0x00, 0x00, 0x02, 0x02, 0x00, 0x00, 0x00, 0x02, 0x06, 0x00, 0x00, 0x00, 0x02,
                             0x04, 0x00, 0x00, 0x00, 0x03, 0x18, 0x00, 0x00, 0x80, 0x01, 0xE0, 0x08, 0x00, 0xC0, 0x00, 0x00,
                             0x37, 0x00, 0x3E, 0x00, 0x00, 0xE0, 0x80, 0x03, 0x00, 0x00, 0x00, 0x7F, 0x00, 0x00, 0x00, 0x00,
                             0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };


const uint8_t partlyCloudy[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                 0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0x8E, 0x07, 0x00, 0x00, 0x80, 0x01, 0x08,
                                 0x00, 0x00, 0x40, 0x00, 0x30, 0x00, 0x00, 0x20, 0x00, 0x20, 0x00, 0x00, 0x3C, 0x00, 0x40, 0x00,
                                 0x80, 0x03, 0x00, 0x80, 0x07, 0x60, 0x00, 0x00, 0x00, 0x18, 0x10, 0x00, 0x00, 0x00, 0x30, 0x08,
                                 0x00, 0x00, 0x00, 0x60, 0x08, 0x00, 0x00, 0x00, 0x40, 0x08, 0x00, 0x00, 0x00, 0x40, 0x08, 0x00,
                                 0x00, 0x00, 0x80, 0x08, 0x00, 0x00, 0x00, 0x40, 0x18, 0x00, 0x00, 0x00, 0x40, 0x30, 0x00, 0x00,
                                 0x00, 0x20, 0xE0, 0x00, 0x00, 0x00, 0x10, 0x80, 0x1F, 0x00, 0x00, 0x0C, 0x00, 0x30, 0x00, 0xFC,
                                 0x03, 0x00, 0xC0, 0xC3, 0x03, 0x00, 0x00, 0x00, 0x3C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };


const uint8_t cloudy[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0,
                           0x07, 0x00, 0x00, 0x00, 0x70, 0x18, 0x00, 0x00, 0x00, 0x08, 0x20, 0x80, 0x07, 0x00, 0x08, 0x20,
                           0x60, 0x18, 0x00, 0x18, 0x00, 0x18, 0x20, 0x00, 0xE0, 0x07, 0x08, 0x40, 0x00, 0x00, 0x80, 0x07,
                           0x80, 0x03, 0x00, 0x60, 0x00, 0x00, 0x0C, 0x00, 0x10, 0x00, 0x00, 0x18, 0x00, 0x10, 0x00, 0x00,
                           0x10, 0x00, 0x18, 0x00, 0x00, 0x10, 0x00, 0x10, 0x00, 0x00, 0x10, 0x00, 0x30, 0x00, 0x00, 0x10,
                           0x00, 0x60, 0x00, 0x00, 0x08, 0x00, 0x86, 0x07, 0x00, 0x07, 0x80, 0x01, 0x38, 0xFC, 0x00, 0x40,
                           0x00, 0xC0, 0x03, 0x00, 0x3C, 0x80, 0x01, 0x00, 0x00, 0x06, 0x00, 0x02, 0x00, 0x00, 0x02, 0x00,
                           0x04, 0x00, 0x00, 0x02, 0x00, 0x04, 0x00, 0x00, 0x02, 0x00, 0x04, 0x07, 0x00, 0x1C, 0x00, 0xE3,
                           0x18, 0x00, 0xE0, 0xF8, 0x30, 0x20, 0x00, 0x00, 0x07, 0x10, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00,
                           0x03, 0x00, 0x80, 0x00, 0x00, 0x04, 0x00, 0x40, 0x00, 0x00, 0x04, 0x00, 0x40, 0x00, 0x00, 0x04,
                           0x00, 0x80, 0x00, 0x00, 0x04, 0x00, 0x00, 0x03, 0x00, 0x02, 0x00, 0x00, 0x1E, 0xF8, 0x01, 0x00,
                           0x00, 0xE0, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                           0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };


const uint8_t lightRain[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x00, 0x00, 0x00,
                              0x80, 0xC3, 0x01, 0x00, 0x00, 0x60, 0x00, 0x02, 0x00, 0x00, 0x10, 0x00, 0x0C, 0x00, 0x00, 0x08,
                              0x00, 0x08, 0x00, 0x00, 0x0F, 0x00, 0x10, 0x00, 0xE0, 0x00, 0x00, 0xE0, 0x01, 0x18, 0x00, 0x00,
                              0x00, 0x06, 0x04, 0x00, 0x00, 0x00, 0x0C, 0x02, 0x00, 0x00, 0x00, 0x18, 0x02, 0x00, 0x00, 0x00,
                              0x10, 0x02, 0x00, 0x00, 0x00, 0x10, 0x02, 0x00, 0x00, 0x00, 0x10, 0x02, 0x00, 0x00, 0x00, 0x10,
                              0x06, 0x00, 0x00, 0x00, 0x10, 0x0C, 0x00, 0x00, 0x00, 0x08, 0x38, 0x00, 0x00, 0x00, 0x04, 0xE0,
                              0x07, 0x00, 0x00, 0x03, 0x00, 0x0C, 0x00, 0xFF, 0x00, 0x00, 0xF0, 0xF0, 0x00, 0x00, 0x00, 0x00,
                              0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00,
                              0x01, 0x00, 0x00, 0x20, 0x80, 0x00, 0x00, 0x00, 0x20, 0x80, 0x00, 0x00, 0x00, 0x10, 0x40, 0x00,
                              0x00, 0x00, 0x10, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00,
                              0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
                              0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                              0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };


const uint8_t moderateRain[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x00, 0x00, 0x00,
                                 0x80, 0xC3, 0x01, 0x00, 0x00, 0x60, 0x00, 0x02, 0x00, 0x00, 0x10, 0x00, 0x0C, 0x00, 0x00, 0x08,
                                 0x00, 0x08, 0x00, 0x00, 0x0F, 0x00, 0x10, 0x00, 0xE0, 0x00, 0x00, 0xE0, 0x01, 0x18, 0x00, 0x00,
                                 0x00, 0x06, 0x04, 0x00, 0x00, 0x00, 0x0C, 0x02, 0x00, 0x00, 0x00, 0x18, 0x02, 0x00, 0x00, 0x00,
                                 0x10, 0x02, 0x00, 0x00, 0x00, 0x10, 0x02, 0x00, 0x00, 0x00, 0x20, 0x02, 0x00, 0x00, 0x00, 0x10,
                                 0x06, 0x00, 0x00, 0x00, 0x10, 0x0C, 0x00, 0x00, 0x00, 0x08, 0x30, 0x00, 0x00, 0x00, 0x04, 0xC0,
                                 0x07, 0x00, 0x00, 0x03, 0x00, 0x0C, 0x00, 0xFF, 0x00, 0x00, 0xF0, 0xF0, 0x00, 0x00, 0x00, 0x00,
                                 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x08, 0x00, 0x00, 0x04, 0x08,
                                 0x04, 0x00, 0x00, 0x04, 0x04, 0x04, 0x00, 0x00, 0x02, 0x04, 0x02, 0x00, 0x00, 0x02, 0x02, 0x02,
                                 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x40, 0x00, 0x00,
                                 0x00, 0x10, 0x20, 0x00, 0x00, 0x00, 0x10, 0x20, 0x00, 0x00, 0x00, 0x08, 0x10, 0x00, 0x00, 0x00,
                                 0x08, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };


const uint8_t heavyRain[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x00, 0x00, 0x00,
                              0x80, 0xC3, 0x01, 0x00, 0x00, 0x60, 0x00, 0x06, 0x00, 0x00, 0x10, 0x00, 0x0C, 0x00, 0x00, 0x08,
                              0x00, 0x08, 0x00, 0x00, 0x0F, 0x00, 0x10, 0x00, 0xE0, 0x00, 0x00, 0xE0, 0x01, 0x18, 0x00, 0x00,
                              0x00, 0x06, 0x04, 0x00, 0x00, 0x00, 0x0C, 0x02, 0x00, 0x00, 0x00, 0x18, 0x02, 0x00, 0x00, 0x00,
                              0x10, 0x02, 0x00, 0x00, 0x00, 0x10, 0x02, 0x00, 0x00, 0x00, 0x20, 0x02, 0x00, 0x00, 0x00, 0x10,
                              0x06, 0x00, 0x00, 0x00, 0x10, 0x0C, 0x00, 0x00, 0x00, 0x08, 0x30, 0x00, 0x00, 0x00, 0x04, 0xC0,
                              0x07, 0x00, 0x00, 0x03, 0x00, 0x1C, 0x00, 0xFF, 0x00, 0x00, 0xF0, 0xF0, 0x00, 0x00, 0x00, 0x00,
                              0x0F, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x40, 0x00, 0x00, 0x81, 0x80,
                              0x40, 0x00, 0x80, 0x80, 0x40, 0x40, 0x00, 0x80, 0x80, 0x40, 0x20, 0x00, 0x80, 0x40, 0x40, 0x20,
                              0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x04, 0x02, 0x00,
                              0x00, 0x04, 0x02, 0x02, 0x00, 0x00, 0x02, 0x02, 0x01, 0x00, 0x00, 0x02, 0x02, 0x01, 0x00, 0x00,
                              0x02, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                              0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

const uint8_t thunderShower[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x00, 0x00, 0x00,
                                 0x80, 0xC3, 0x01, 0x00, 0x00, 0x60, 0x00, 0x06, 0x00, 0x00, 0x10, 0x00, 0x0C, 0x00, 0x00, 0x08,
                                 0x00, 0x08, 0x00, 0x00, 0x0F, 0x00, 0x10, 0x00, 0xE0, 0x00, 0x00, 0xE0, 0x01, 0x18, 0x00, 0x00,
                                 0x00, 0x06, 0x04, 0x00, 0x00, 0x00, 0x0C, 0x02, 0x00, 0x00, 0x00, 0x18, 0x02, 0x00, 0x00, 0x00,
                                 0x10, 0x02, 0x00, 0x00, 0x00, 0x10, 0x02, 0x00, 0x00, 0x00, 0x20, 0x02, 0x00, 0x00, 0x00, 0x10,
                                 0x06, 0x00, 0x00, 0x00, 0x10, 0x0C, 0x00, 0x00, 0x00, 0x08, 0x30, 0x00, 0x00, 0x00, 0x04, 0xC0,
                                 0x07, 0x00, 0x00, 0x03, 0x00, 0x1C, 0x00, 0xFF, 0x00, 0x00, 0xF0, 0xF0, 0x00, 0x00, 0x00, 0x00,
                                 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x10, 0x00, 0x82, 0x00, 0x00, 0x18, 0x00,
                                 0x81, 0x00, 0x00, 0x0C, 0x00, 0x41, 0x00, 0x00, 0x04, 0x80, 0x40, 0x00, 0x00, 0x02, 0x80, 0x20,
                                 0x00, 0x00, 0x7F, 0x40, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x30, 0x08, 0x08, 0x00,
                                 0x00, 0x18, 0x04, 0x04, 0x00, 0x00, 0x08, 0x04, 0x04, 0x00, 0x00, 0x04, 0x02, 0x02, 0x00, 0x00,
                                 0x02, 0x02, 0x02, 0x00, 0x00, 0x03, 0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
                                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

const uint8_t lightSnow[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x00, 0x00, 0x00,
                              0x80, 0xC3, 0x01, 0x00, 0x00, 0x60, 0x00, 0x02, 0x00, 0x00, 0x10, 0x00, 0x0C, 0x00, 0x00, 0x08,
                              0x00, 0x08, 0x00, 0x00, 0x08, 0x00, 0x10, 0x00, 0x80, 0x07, 0x00, 0xE0, 0x01, 0x70, 0x00, 0x00,
                              0x00, 0x06, 0x18, 0x00, 0x00, 0x00, 0x0C, 0x04, 0x00, 0x00, 0x00, 0x18, 0x02, 0x00, 0x00, 0x00,
                              0x10, 0x02, 0x00, 0x00, 0x00, 0x10, 0x02, 0x00, 0x00, 0x00, 0x20, 0x02, 0x00, 0x00, 0x00, 0x10,
                              0x02, 0x00, 0x00, 0x00, 0x10, 0x04, 0x00, 0x00, 0x00, 0x08, 0x0C, 0x00, 0x00, 0x00, 0x04, 0x30,
                              0x00, 0x00, 0x00, 0x03, 0xC0, 0x7F, 0xE0, 0xFF, 0x00, 0x00, 0x80, 0x1F, 0x00, 0x00, 0x00, 0x00,
                              0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x80,
                              0x01, 0x00, 0x00, 0x60, 0x80, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                              0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                              0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                              0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                              0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

const uint8_t moderateSnow[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x00, 0x00, 0x00,
                                 0x80, 0xC3, 0x01, 0x00, 0x00, 0x60, 0x00, 0x02, 0x00, 0x00, 0x10, 0x00, 0x0C, 0x00, 0x00, 0x08,
                                 0x00, 0x08, 0x00, 0x00, 0x08, 0x00, 0x10, 0x00, 0x80, 0x07, 0x00, 0xE0, 0x01, 0x70, 0x00, 0x00,
                                 0x00, 0x06, 0x18, 0x00, 0x00, 0x00, 0x0C, 0x04, 0x00, 0x00, 0x00, 0x18, 0x02, 0x00, 0x00, 0x00,
                                 0x10, 0x02, 0x00, 0x00, 0x00, 0x10, 0x02, 0x00, 0x00, 0x00, 0x20, 0x02, 0x00, 0x00, 0x00, 0x10,
                                 0x02, 0x00, 0x00, 0x00, 0x10, 0x04, 0x00, 0x00, 0x00, 0x08, 0x0C, 0x00, 0x00, 0x00, 0x04, 0x30,
                                 0x00, 0x00, 0x00, 0x03, 0xC0, 0x7F, 0xE0, 0xFF, 0x00, 0x00, 0x80, 0x1F, 0x00, 0x00, 0x00, 0x00,
                                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x0C,
                                 0x30, 0x00, 0x00, 0x03, 0x0C, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                 0x00, 0x60, 0x80, 0x01, 0x00, 0x00, 0x60, 0x80, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

const uint8_t heavySnow[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x00, 0x00, 0x00,
                              0x80, 0xC3, 0x01, 0x00, 0x00, 0x60, 0x00, 0x02, 0x00, 0x00, 0x10, 0x00, 0x0C, 0x00, 0x00, 0x08,
                              0x00, 0x08, 0x00, 0x00, 0x08, 0x00, 0x10, 0x00, 0x80, 0x07, 0x00, 0xE0, 0x01, 0x70, 0x00, 0x00,
                              0x00, 0x06, 0x18, 0x00, 0x00, 0x00, 0x0C, 0x04, 0x00, 0x00, 0x00, 0x18, 0x02, 0x00, 0x00, 0x00,
                              0x10, 0x02, 0x00, 0x00, 0x00, 0x10, 0x02, 0x00, 0x00, 0x00, 0x20, 0x02, 0x00, 0x00, 0x00, 0x10,
                              0x02, 0x00, 0x00, 0x00, 0x10, 0x04, 0x00, 0x00, 0x00, 0x08, 0x0C, 0x00, 0x00, 0x00, 0x04, 0x30,
                              0x00, 0x00, 0x00, 0x03, 0xC0, 0x7F, 0xE0, 0xFF, 0x00, 0x00, 0x80, 0x1F, 0x00, 0x00, 0x00, 0x00,
                              0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                              0x00, 0x00, 0xC0, 0xC0, 0xC0, 0xC0, 0x00, 0xC0, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00,
                              0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                              0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x0C, 0x0C, 0x00, 0x00, 0x0C, 0x0C, 0x0C, 0x00, 0x00,
                              0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                              0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

const uint8_t sleet[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x00, 0x00, 0x00,
                          0x80, 0xC3, 0x01, 0x00, 0x00, 0x60, 0x00, 0x02, 0x00, 0x00, 0x10, 0x00, 0x0C, 0x00, 0x00, 0x08,
                          0x00, 0x08, 0x00, 0x00, 0x08, 0x00, 0x10, 0x00, 0x80, 0x07, 0x00, 0xE0, 0x01, 0x70, 0x00, 0x00,
                          0x00, 0x06, 0x18, 0x00, 0x00, 0x00, 0x0C, 0x04, 0x00, 0x00, 0x00, 0x18, 0x02, 0x00, 0x00, 0x00,
                          0x10, 0x02, 0x00, 0x00, 0x00, 0x10, 0x02, 0x00, 0x00, 0x00, 0x20, 0x02, 0x00, 0x00, 0x00, 0x10,
                          0x02, 0x00, 0x00, 0x00, 0x10, 0x04, 0x00, 0x00, 0x00, 0x08, 0x0C, 0x00, 0x00, 0x00, 0x04, 0x30,
                          0x00, 0x00, 0x00, 0x03, 0xC0, 0x7F, 0xE0, 0xFF, 0x00, 0x00, 0x80, 0x1F, 0x00, 0x00, 0x00, 0x00,
                          0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x02, 0x00, 0x00, 0x20, 0x00, 0x01, 0x00, 0x00, 0x23, 0x0C,
                          0x31, 0x00, 0x00, 0x13, 0x8C, 0x30, 0x00, 0x00, 0x10, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x08, 0x20, 0x00, 0x00, 0x01, 0x04, 0x10, 0x00,
                          0x00, 0x61, 0x84, 0x11, 0x00, 0x80, 0x60, 0x82, 0x09, 0x00, 0x80, 0x00, 0x02, 0x08, 0x00, 0x00,
                          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };





/*





//net:10 * 10    16 * 10
const uint8_t netIcon[] = { 0x78, 0x00, 0x9C, 0x00, 0x82, 0x01, 0xCF, 0x03, 0xE7, 0x03, 0xE1, 0x03, 0x9D, 0x03, 0x9A, 0x01,
                            0x8C, 0x00, 0x78, 0x00 };

//refresh 8 * 10
const uint8_t refresh[] = { 0x10, 0x30, 0x7C, 0x7E, 0x37, 0x13, 0xC3, 0xE7, 0x7E, 0x3C };

//24 * 24  14 36
const uint8_t umbrella[] = { 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x3F, 0x00, 0xC0, 0xC0, 0x00, 0x30, 0x00, 0x03, 0x08,
                             0x00, 0x04, 0x04, 0x00, 0x08, 0x02, 0x00, 0x10, 0x9E, 0x73, 0x1E, 0x62, 0x8C, 0x11, 0x00, 0x08,
                             0x00, 0x00, 0x08, 0x00, 0x00, 0x08, 0x00, 0x00, 0x08, 0x00, 0x00, 0x08, 0x00, 0x00, 0x08, 0x00,
                             0x00, 0x08, 0x00, 0x00, 0x08, 0x00, 0x00, 0x08, 0x00, 0x00, 0x88, 0x00, 0x00, 0x88, 0x00, 0x00,
                             0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

*/