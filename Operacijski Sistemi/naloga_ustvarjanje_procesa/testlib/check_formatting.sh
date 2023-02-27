#!/usr/bin/bash
source test_format_lib.sh

echo "-----------"
echo "Test title:"
echo "-----------"
echo_test_title "Lorem Ipsum"

echo "--------"
echo "Test ok:"
echo "--------"
echo_ok "Lorem ipsum dolor sit amet, consectetur adipiscing elit."

echo "----------"
echo "Test warn:"
echo "----------"
echo_warn "Lorem ipsum dolor sit amet, consectetur adipiscing elit."

echo "----------"
echo "Test fail:"
echo "----------"
echo_fail "Lorem ipsum dolor sit amet, consectetur adipiscing elit."

echo "-------------"
echo "Test section:"
echo "-------------"
echo_section "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Morbi \
elementum imperdiet dolor, in molestie lectus. Aenean rutrum tellus vitae odio \
condimentum finibus. Aliquam ac felis id lectus laoreet porttitor eget ac \
quam. Etiam non pellentesque eros, et condimentum nulla."

echo "-------------------"
echo "Test output format:"
echo "-------------------"
echo "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Morbi elementum \
imperdiet dolor, in molestie lectus. Aenean rutrum tellus vitae odio \
condimentum finibus. Aliquam ac felis id lectus laoreet porttitor eget ac \
quam. Etiam non pellentesque eros, et condimentum nulla." | pipe_output_format

echo "-------------------"
echo "Test stderr format:"
echo "-------------------"
echo "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Morbi elementum \
imperdiet dolor, in molestie lectus. Aenean rutrum tellus vitae odio \
condimentum finibus. Aliquam ac felis id lectus laoreet porttitor eget ac \
quam. Etiam non pellentesque eros, et condimentum nulla." | pipe_stderr_format
