#include <check.h>
#include "dictionary.h"
#include <stdlib.h>

#define DICTIONARY "wordlist.txt"
#define TESTDICT "test_worlist.txt"

START_TEST(test_dictionary_normal)
{
    hashmap_t hashtable[HASH_SIZE];
    ck_assert(load_dictionary(TESTDICT, hashtable));
    // Here we can test if certain words ended up in certain buckets
    // to ensure that our load_dictionary works as intended. I leave
    // this as an exercise.
}
END_TEST

// START_TEST(test_check_word_normal)
// {
//     hashmap_t hashtable[HASH_SIZE];
//     load_dictionary(DICTIONARY, hashtable);
//     const char* correct_word = "Justice";
//     const char* punctuation_word_2 = "pl.ace";
//     ck_assert(check_word(correct_word, hashtable));
//     ck_assert(!check_word(punctuation_word_2, hashtable));
//     // Test here: What if a word begins and ends with "?
// }
// END_TEST

// START_TEST(test_check_words_normal)
// {
//     hashmap_t hashtable[HASH_SIZE];
//     load_dictionary(DICTIONARY, hashtable);
//     char* expected[3];
//     expected[0] = "sogn";
//     expected[1] = "skyn";
//     expected[2] = "betta";
//     char *misspelled[MAX_MISSPELLED];
//     FILE *fp = fopen("test1.txt", "r");
//     int num_misspelled = check_words(fp, hashtable, misspelled);
//     ck_assert(num_misspelled == 3);
//     bool test = strlen(misspelled[0]) == strlen(expected[0]);
//     int len1 = strlen(misspelled[0]);
//     int len2 = strlen(expected[0]);
//     ck_assert_msg(test, "%d!=%d", len1, len2);
//     ck_assert_msg(strcmp(misspelled[0], expected[0]) == 0);
//     ck_assert_msg(strcmp(misspelled[1], expected[1]) == 0);
//     ck_assert_msg(strcmp(misspelled[2], expected[2]) == 0);
// }
// END_TEST

// MY TESTS

// TEST IF NULL
// *WORKS*
START_TEST(test_check_word_empty_hashtable)
{
    hashmap_t hashtable[HASH_SIZE];
    for (int i = 0; i < HASH_SIZE; i++)
    hashtable[i] = NULL;

    char * word = "empty";
        
    ck_assert(!check_word(word, hashtable));
    

}
END_TEST

START_TEST(test_null_input)
{
    hashmap_t hashtable[HASH_SIZE];
    load_dictionary(DICTIONARY, hashtable);
    const char* null_word = "";
    ck_assert(!check_word(null_word,hashtable));
}
END_TEST
// *WORKS*
START_TEST(test_check_word_really_extra_long_word)
{
    // Check for word equal to 45characters, doesnt matter if misspelled
    hashmap_t hashtable[HASH_SIZE];
    load_dictionary(DICTIONARY, hashtable);
    const char* really_extra_long_word = "CaliforniaNorthDakotaMontanaArizonaWashingtonCaliforniaNorthDakotaMontanaArizonaWashingtonCaliforniaNorthDakotaMontanaArizonaWashington";
    ck_assert(!check_word(really_extra_long_word, hashtable));
}
END_TEST
// *WORKS?*
// START_TEST(test_check_single_word_overflow_dictionary)
// {
//     hashmap_t hashtable[HASH_SIZE];
//     load_dictionary("test2.txt", hashtable);
//     int word1_hash = hash_function("Historicallyorganizationsandgovernmentshaveta");
//     char *word1 = hashtable[word1_hash];
//     ck_assert(strcmp(word1, "Historicallyorganizationsandgovernmentshaveta") == 0);
//     ck_assert(LENGTH == strlen(word1));
// }
// END_TEST

// START_TEST(test_check_word_leading_trailing_punct){
//     hashmap_t hashtable[HASH_SIZE];
//     load_dictionary(DICTIONARY, hashtable);
//     char * correctEmbeddedPunct[] = {"I'll", "we'll","we'd","you're","can't","that's", "quadrilateral's"};
//     char * incorrectPunct[] = {",duck","?duck","duck,","duck!","duck.","d'uck","re-use"};
//     const int CHECK_SIZE = sizeof(correctEmbeddedPunct)/sizeof(correctEmbeddedPunct[0]);
    

//     int i;
//     for (i = 0; i < CHECK_SIZE; i++) {
//      ck_assert(check_word(correctEmbeddedPunct[i], hashtable));
//          ck_assert(!check_word(incorrectPunct[i], hashtable));
//     }

// }
// END_TEST

START_TEST(test_check_word_buffer_overflow2)
{
    hashmap_t hashtable[HASH_SIZE];
    load_dictionary(DICTIONARY, hashtable);
    char incorrect_word[500000];
    for (int i=0;i< 499999; i++) 
        incorrect_word[i] = 'A';
    incorrect_word[56] = '\0'; // 57 break
    ck_assert(!check_word(incorrect_word, hashtable));
}
END_TEST

//checking case sensitiveness
START_TEST(test_check_word_case)
{   
    node* hashtable[HASH_SIZE];
    load_dictionary(DICTIONARY, hashtable);
    const char* correct_word = "IEEE";
    const char* lcase = "ieee";
    ck_assert(check_word(correct_word, hashtable));
    ck_assert(check_word(lcase, hashtable));
}
END_TEST

Suite *
check_word_suite(void)
{
    Suite * suite;
    TCase * check_word_case;
    suite = suite_create("check_word");
    check_word_case = tcase_create("Core");
    // tcase_add_test(check_word_case, test_check_word_normal);
    // tcase_add_test(check_word_case, test_check_words_normal);
    tcase_add_test(check_word_case, test_check_word_empty_hashtable);
    tcase_add_test(check_word_case, test_check_word_buffer_overflow2);
    tcase_add_test(check_word_case, test_null_input);
    tcase_add_test(check_word_case, test_check_word_really_extra_long_word);
    // tcase_add_test(check_word_case, test_check_single_word_overflow_dictionary);
    // tcase_add_test(check_word_case, test_check_word_leading_trailing_punct);
    suite_add_tcase(suite, check_word_case);

    return suite;
}

int
main(void)
{
    int failed;
    Suite *suite;
    SRunner *runner;
    
    suite = check_word_suite();
    runner = srunner_create(suite);
    srunner_run_all(runner, CK_NORMAL);
    failed = srunner_ntests_failed(runner);
    srunner_free(runner);
    return (failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE);
}

