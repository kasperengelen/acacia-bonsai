#!/bin/zsh

CONF=best
SYFCO=$(which syfco 2> /dev/null) || { echo "syfco not found, aborting."; exit 1 }

ACABON=/acacia-bonsai/build_$CONF/src/acacia-bonsai
[[ -x $ACABON ]] || { echo "$ACABON: file not found, aborting."; exit 1 }

FILE=$1
PART=$(mktemp)
LTL=$($SYFCO $FILE -f ltlxba -m fully -pf $PART)

parttoinsouts () {
    while IFS= read line; do
        line=$(echo "$line" | sed 's/[[:space:]]*$//;s/[[:space:]]\+/,/g')
        head=${line/,*/}
        args=${line/$head,/}
        case "$head" in
            .inputs) ins=$args;;
            .outputs) outs=$args;;
        esac
    done < $1
}

parttoinsouts $PART

$ACABON -c BOTH --formula="$LTL" --ins="$ins" --outs="$outs"

rm -f $PART
