#ifndef UNITTESTER_H
#define UNITTESTER_H

class UnitTester
{
public:
    UnitTester();

    void testProtocolDao(); // TODO add more protocols

    // DATA CONVERSION
    void testDirectConversion();
    void testIndirectConversion(); // TODO add more conversion methods

    // Publisher-Subscribe for PacketListener and DataAnalyzer
    void testPS(); // TODO refactor packet listener
};

#endif // UNITTESTER_H
