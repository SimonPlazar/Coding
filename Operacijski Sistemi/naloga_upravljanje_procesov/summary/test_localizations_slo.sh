declare -A TEST_LOCALIZATIONS=(
# run_tests.sh
['TEST RESULTS']='REZULTATI TESTOV'
['TEST PASSED']='TEST USPEŠEN'
['TEST FAILED']='TEST NEUSPEŠEN'
['TEST TO BE CHECKED MANUALLY']='TEST BO PREVERJEN ROČNO'

# test_common_lib.sh
['Subtest']='Podtest'
['Actual exit status: %s']='Dejanska izhodna vrednost: %s'
['Expected exit status: %s']='Pričakovana izhodna vrednost: %s'
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
['  - working of the flag -c']='  - delovanje zastavice -c'

# Test 2
['  - working of the flag -d']='  - delovanje zastavice -d'

# Test 3
['  - working of the flag -e']='  - delovanje zastavice -e'

#Test 4
['  - working of the mixed flags (-c, -d, -e)']='  - delovanje mešanih zastavic (-c, -d, -e)'

# Test 5
['  - program help']='  - pomoč programa'
['  - program start without flags']='  - zagon programa brez zastavic'

# Test 6
['  - invalid flag']='  - neveljavna zastavica'
['  - flag missing argument']='  - zastavici manjka argument'
)
