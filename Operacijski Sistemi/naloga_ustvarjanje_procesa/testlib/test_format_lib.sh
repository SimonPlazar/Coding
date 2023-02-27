#!/usr/bin/bash
FORMAT_WIDTH=80

echo_test_title () {
    arg_cat="$*"
    arg_len=${#arg_cat}
    prefix_len=$(((FORMAT_WIDTH-arg_len)/2))
    sufix_len=$((FORMAT_WIDTH-arg_len-prefix_len))

    echo
    tput bold; tput setaf 4; tput setab 7
    printf "%${prefix_len}s"
    printf '%s' "$arg_cat"
    printf "%${sufix_len}s\n"
    tput sgr0; tput el
}

echo_section () {
    tput bold
    echo
    echo "$*"
    tput sgr0
}

echo_fail () {
    echo "$(tput setaf 1)$*$(tput sgr0)"
}

echo_ok () {
    echo "$(tput setaf 2)$*$(tput sgr0)"
}

echo_warn () {
    echo "$(tput setaf 3)$*$(tput sgr0)"
}

pipe_format_wordwrap () {
    local format_set=$1
    local format_reset=$2

    while read -r 
    do
        input_line="${REPLY}"
        echo "$input_line" | sed 's/\t/    /g' | fold -w ${FORMAT_WIDTH} -s | while read -r 
        do
            fold_line="${REPLY}"
            printf '%s%s' "$format_set" "${fold_line}"
            remainder=$((FORMAT_WIDTH-${#fold_line}))
            if [ $remainder -gt 0 ]
            then
                printf "%${remainder}s" 
            fi
            printf '%s\n' "$format_reset"
        done 
    done

}

pipe_stderr_format () {
    pipe_format_wordwrap "$(tput bold; tput setaf 0; tput setab 1)" "$(tput sgr0)"
}

pipe_output_format () {
    pipe_format_wordwrap "$(tput setaf 0; tput setab 7)" "$(tput sgr0)"
}

