#include <QtGui>


class CoreLibInitializer
{
public:
    CoreLibInitializer()
    {
        Q_INIT_RESOURCE(CommonIcons);
    }
};

CoreLibInitializer coreInitializer;



