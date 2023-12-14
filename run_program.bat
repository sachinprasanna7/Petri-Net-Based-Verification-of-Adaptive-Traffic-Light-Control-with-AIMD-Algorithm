@echo off

REM Setting the paths to the folders containing the verification and validation code
set VERIFICATION_FOLDER=Verification
set VALIDATION_FOLDER=Validation

REM Changing the current working directory to the verification code folder
cd %VERIFICATION_FOLDER%

REM Compiling and executing the C++ verification code
g++ VerificationCode.cpp -o VerificationCode
.\VerificationCode

REM Executing the Python script to generate the reachability graph
python -u "plot.py"

echo --------------------------------------------

REM Changing the current working directory back to the original folder
cd ..

REM Changing the current working directory to the validation code folder
cd %VALIDATION_FOLDER%

REM Compiling and executing the C++ validation code
g++ ValidationCode.cpp -o ValidationCode
.\ValidationCode

REM Changing the current working directory back to the original folder
cd ..

echo --------------------------------------------


