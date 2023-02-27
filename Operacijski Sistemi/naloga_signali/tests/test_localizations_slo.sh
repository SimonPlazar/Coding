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

# Test 0
['  - an implementation is available and can be tested']='  - implementacija je na voljo in se lahko preizkusi'
['looking for executable']='iskanje izvedljivega modula'
['Executable not set.']='Izvedljiv modul ni nastavljen.'
['Executable not found:']='Izvedljiv modul ni najden:'
['Executable found:']='Izvedljiv modul je najden:'
['Could not find valgrind, tests will be incomplete.']='Program valgrind ni bil najden, preizkusi bodo nepopolni.'

# Test 1
['  - performance of past jobs in ascending, descending and random order']='  - delovanje preteklih poslov v naraščajočem, padajočem in naključnem vrstnem redu'

# Test 2
['  - performance of future jobs in ascending, descending and random order']='  - delovanje prihodnjih poslov v naraščajočem, padajočem in naključnem vrstnem redu'

# Test 3
['  - performance of past jobs with simultaneous execution time']='  - delovanje preteklih poslov s hkratnim časom izvedbe'

#Test 4
['  - performance of future jobs with simultaneous execution time']='  - delovanje prihodnjih poslov s hkratnim časom izvedbe'

# Test 5
['  - performance of past and future jobs']='  - delovanje preteklih in prihodnjih poslov'

# Test 6
['  - performance without jobs']='  - delovanje brez poslov'

# Test 7
['  - performance of signals SIGTERM and SIGINT']='  - delovanje signalov SIGTERM in SIGINT'

# Test 8
['  - missing required argument']='  - manjkajoč obvezen argument'
)
