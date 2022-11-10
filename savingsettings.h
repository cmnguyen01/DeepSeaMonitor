#ifndef SAVINGSETTINGS_H
#define SAVINGSETTINGS_H


class savingsettings
{
public:
    savingsettings();
    ~savingsettings();

    static void loadSettings();
    static void saveSettings();
};

#endif // SAVINGSETTINGS_H
