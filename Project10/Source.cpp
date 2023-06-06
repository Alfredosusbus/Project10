#include <Windows.h>
#include <time.h>
#include <cstdlib>
#include "StartForm.h"

using namespace System;
using namespace System::Windows::Forms;
int main()
{
    srand(time(NULL));

    Application::EnableVisualStyles();
    Application::Run(gcnew StartForm());

    return 0;
}