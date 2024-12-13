BUILD_DIR="build"
TESTS_DIR="test/Random4-C-5w"
RESULTS_DIR="wyniki/Random4-C-5w"

for program in "$BUILD_DIR"/*; do

  program_name=$(basename "$program")

  for test_file in "$TESTS_DIR"/*.gr; do
    test_name=$(basename "$test_file" .gr)
    source_file="${test_file%.*}.ss"
    result_file="$RESULTS_DIR"/"$program_name"-"$test_name".ss.res
    "$program" -d "$test_file" -ss "$source_file" -oss "$result_file"
    #source_file="${test_file%.*}.p2p"
    #result_file="$RESULTS_DIR"/"$program_name"-"$test_name".p2p.res
    #"$program" -d "$test_file" -p2p "$source_file" -op2p "$result_file"
  done
done