#include "SavingScore.hpp"
#include "../Managers/ResourceManager.hpp"

const size_t kNumberRecordsInTop = 10;
const char*  kTopScoreFilePath   = "Top";

Vector<int> getTopScore()
{
	FILE* score_file = fopen(kTopScoreFilePath, "r");
	if (score_file == nullptr)
		return Vector<int>();
	
	Vector<int> score;
	long curr_score = 0;
	while(fscanf(score_file, "%d", &curr_score) == 1)
		score.PushBack(curr_score);

	fclose(score_file);

	return score;
}

void putTopScoreInFile(const Vector<int>& top_scores)
{
	FILE* score_file = fopen(kTopScoreFilePath, "w");

	const size_t records_number = top_scores.Size();
	for (size_t i = 0; i < records_number; i++)
		fprintf(score_file, "%d\n", top_scores[i]);
	fclose(score_file);
}

int comparator(const void* a, const void* b)
{
	return *(int*)b - *(int*)a;
}

void updateTopScores()
{
	const long new_population_value = ResourceManager::current_manager->getUserRes().population;

	Vector<int> top_scores = getTopScore();
	if (top_scores.Size() < kNumberRecordsInTop)
		top_scores.PushBack(new_population_value);

	qsort(&(*top_scores.Begin()), top_scores.Size(), sizeof(Vector<int>::value_type), comparator);

	for (size_t i = 0; i < top_scores.Size(); i++)
	{
		if (top_scores[i] < new_population_value)
		{
			for (size_t j = i + 1; j < top_scores.Size(); j++)
				top_scores[j] = top_scores[j - 1];
			top_scores[i] = new_population_value;
		}
	}

	putTopScoreInFile(top_scores);
}