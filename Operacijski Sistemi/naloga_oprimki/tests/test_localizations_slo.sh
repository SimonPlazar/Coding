declare -A TEST_LOCALIZATIONS=(
# run_tests.sh
['TEST RESULTS']='REZULTATI TESTOV'
['TEST PASSED']='TEST USPEŠEN'
['TEST FAILED']='TEST NEUSPEŠEN'
['TEST TO BE CHECKED MANUALLY']='TEST BO PREVERJEN ROČNO'

# test_common_lib.sh
['Subtest']='Podtest'
['Actual exit status: ']='Dejanska izhodna vrednost: '
['Expected exit status: ']='Pričakovana izhodna vrednost: '
['Actual output:']='Dejanski izhod:'
['Expected output:']='Pričakovan izhod:'
['Is the same as expected output.']='Je enak kot pričakovan izhod.'
['Is the same as actual output.']='Je enak kot dejanski izhod.'
['Diff between actual and expected outputs:']='Razlika med dejanskim in pričakovanim izhodom:'
['SUBTEST PASSED']='PODTEST USPEŠEN'
['SUBTEST FAILED']='PODTEST NEUSPEŠEN'
['SUBTEST TO BE CHECKED MANUALLY']='PODTEST BO PREVERJEN ROČNO'
['TEST PASSED: All subtests passed.']='TEST USPEŠEN: Vsi podtesti so uspeli.'
['TEST FAILED: At least one subtest failed.']='TEST NEUSPEŠEN: Vsaj en izmed podtestov ni uspel.'
['TEST TO BE CHECKED MANUALLY: At least one subtest to be checked manually.']='TEST BO PREVERJEN ROČNO: Vsaj en izmed podtestov bo preverjen ročno.'

# All Tests
['This test checks:']='Ta test preveri:'
['Could not find valgrind, test will be incomplete.']='Program valgrind ni bil najden, preizkusi bodo nepopolni.'

# Test 0
['  - an implementation is available and can be tested']='  - implementacija je na voljo in se lahko preizkusi'
['looking for executable']='iskanje izvedljivega modula'
['Executable not set.']='Izvedljiv modul ni nastavljen.'
['Executable not found:']='Izvedljiv modul ni najden:'
['Executable found:']='Izvedljiv modul je najden:'

# Test 1
['  - reading of standard input and writing to standard output']='  - branje iz standardnega vhoda in pisanje na standardni izhod'
['  - reading and writing of files']='  - branje in pisanje zbirk'
['  - reading and writing of file descriptors']='  - branje in pisanje oprimkov'
['  - all possible combinations between them']='  - vse možne kombinacije med njimi'

# Test 2
['  - reading and writing larger amounts of data']='  - branje in pisanje večjih količin podatkov'

# Test 3
['  - slow reading']='  - počasno branje'

# Test 4
['  - help of the program']='  - izpis pomoči programa'

# Test 5
['  - invalid flag']='  - neveljavna zastavica'
['  - flag missing argument']='  - zastavici manjka argument'
['  - input file does not exist']='  - vhodna zbirka ne obstaja'
['  - output file already exists']='  - izhodna zbirka že obstaja'
['  - input file descriptor is not a valid number']='  - oprimek za branje ni veljavno število'
['  - output file descriptor is not a valid number']='  - oprimek za pisanje ni veljavno število'
['  - reading error']='  - napaka pri branju'
['  - writing error']='  - napaka pri pisanju'
)
