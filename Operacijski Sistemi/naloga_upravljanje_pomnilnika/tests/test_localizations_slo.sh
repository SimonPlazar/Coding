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
['  - single allocations']='  - posamezne alokacije'

# Test 2
['  - multiple sequential allocations']='  - več zaporednih alokacij'

# Test 3
['  - multiple parallel allocations']='  - več vzporednih alokacij'

#Test 4
['  - multiple parallel reversed allocations']='  - več vzporednih obratnih alokacij'

# Test 5
['  - multiple parallel random allocations']='  - več vzporednih naključnih alokacij'

# Test 6
['  - multiple simultaneous sequential allocations']='  - več hkratnih zaporednih alokacij'
['  - multiple simultaneous parallel allocations']='  - več hkratnih vzporednih alokacij'
['  - multiple simultaneous parallel reversed allocations']='  - več hkratnih vzporednih obratnih alokacij'
['  - multiple simultaneous parallel random allocations']='  - več hkratnih vzporednih naključnih alokacij'

# Test 7
['  - mymalloc returns NULL on error']='  - mymalloc vrne NULL v primeru napake'
['  - myfree works with NULL']='  - myfree deluje z NULL'

# Test 8
['  - different memory alocation profiles']='  - različne profile alokacij pomnilnika'
['  - different memory related errors']='  - različne napake povezane s pomnilnikom'
)
