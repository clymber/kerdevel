#!/bin/bash -

function find_debugfs()
{
    mount | awk '/^debugfs on .* type debugfs/{print $3}'
}

# @desc - grep function name from /sys/kernel/debug/tracing/trace
# @usage - filter_trace <pattern> [max match count] [max lines to filter]
function filter_trace() (
    REGX=${1:?"no regx"}  # regular expression
    MAXMATCH=${2:-3}      # max match count
    MAXLINES=${3:-1000}   # max number record

    awk -v pattern="$REGX" -v max_match="$MAXMATCH" -v max_lines="$MAXLINES" '
        function enque_ring_buff(ring_buff) {
            ring_buff[FNR] = $0
            if (FNR-5 in ring_buff) {
                delete ring_buff[FNR-5]; n_ignore += 1
            }
        }
        function print_clear_ring_buff(ring_buff) {
            if (n_ignore > 0) {
                print " >>>>>>>>>>>>>>>>> "n_ignore" lines ignored <<<<<<<<<<<"
                n_ignore = 0
            }
            for (nr in ring_buff) {
                print ring_buff[nr]
            }
            delete ring_buff
        }

        BEGIN {
            n_match   = 0                     # number of matched
            n_headers = 12                    # 12 lines of headers
            max_match = 0 + max_match         # convert from string to integer
            max_lines = max_lines + n_headers # max output lines
            n_ignore = 0
        }
        
        $0 ~ pattern {
            print_clear_ring_buff(ring_buff)
            print; ++n_match; tailing = 5; next;
        }

        FNR < n_headers { print; next; }
        FNR > max_lines { print "[WORNING] message overflow, FNR=" FNR; exit; }
        tailing > 0 { tailing -= 1; print; next; }
        n_match >= max_match { exit }
        
        { enque_ring_buff(ring_buff) }
        ' $(find_debugfs)/tracing/trace
)
