/*음악 추천 프로그램*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define SIZE 50
#define LENGTH 50

struct music
{ 
	int number; // 사용자가 듣고 싶은 음악을 숫자로 받기 위해서
	char genre[10]; // 장르 구분: jazz, rock, folk, pop, ost
	char mood[20]; // 분위기 구분: excite, calm, calm and excite
	char name[LENGTH]; 
}; 

int main(void)
{
	struct music m[SIZE] = {
		{1, "jazz", "calm", "my way"},
		{2, "rock", "excite", "satisfaction"},
		{3, "rock", "excite", "another one bites the dust"},
		{4, "ost", "calm", "remember me"},
		{5, "pop", "excite", "billie jean"},
		{6, "pop", "calm&excite", "if I were a boy"},
		{7, "ost", "excite", "drive it like you stole it"},
		{8, "jazz", "calm", "my funny valentine"},
		{9, "rock", "calm&excite", "champagne supernova"},
		{10, "rock", "excite", "back in black"},
		{11, "pop", "calm&excite", "man in the mirror"},
		{12, "folk", "calm&excite", "like a rolling stone"},
		{13, "jazz", "calm", "what a wonderful world"},
		{14, "folk", "calm", "blowin' in the wind"},
		{15, "folk", "calm", "pink moon"},
		{16, "ost", "calm&excite", "tell me if you wanna go home"},
		{17, "jazz", "calm", "fly me to the moon"},
		{18, "rock", "excite", "come together"},
		{19, "ost", "calm&excite", "you've got a friend in me"},
		{20, "pop", "excite", "grace kelly"}
	};

//프로그램에 음악 등록하는 알고리즘
	for (int i = 20;i < SIZE;i++)
	{
		int n;
		printf("음악 입력\n");
		printf("0 - 중지\n1 - 계속\n");
		scanf_s("%d", &n);
		if (n == 0)
			break;

		printf("\n장르 구분: jazz, rock, folk, pop, ost\n");
		printf("분위기 구분: excite, calm&excite, calm\n");
		printf("음악을 입력하시오 ");
		printf("(장르enter분위기enter제목):\n");

		m[i].number = i + 1;
		printf("\n음악 번호: %d\n", i + 1);
		scanf_s("%s", m[i].genre, 10);
		scanf_s("%s", m[i].mood, 20);
		// 공백문자때문에 gets_s()함수로 받으려 하였으나, 작동안하여 _getche()함수로 일일이 받음.
		for (int j = 0;j < LENGTH;j++)
		{
			m[i].name[j] = _getche();
			if (m[i].name[j] == '\r') // 엔터 입력 시, '\r' 할당된 배열 NULL문자로 초기화 -> 제목 입력 중단
			{
				m[i].name[j] = NULL;
				break;
			}
		}
		printf("\n\n");
	}

//사용자로부터 음악 선택 받는 알고리즘
	while (1)
	{
		int n;
		printf("\n음악번호를 입력하시오: ");
		scanf_s("%d", &n);
		n--;
		printf("playlist\n"); // playlist 출력
		printf("%s\n", m[n].name);

//선택 받은 음악 기반으로 장르별, 분위기별 음악 분류하는 알고리즘
		char genre[SIZE][LENGTH]; // 선택 받은 음악과 같은 장르의 음악 저장
		char mood[SIZE][LENGTH]; // 선택 받은 음악과 같은 분위기의 음악 저장
	
		int index1 = 0, index2 = 0;
		for (int i = 0;i < SIZE;i++)
		{
			if (i == n) // 선택받은 음악은 제외
				continue;
			int x = strcmp(m[i].genre, m[n].genre); // 선택 받은 음악과 장르가 같으면
			if (x == 0)
			{
				strcpy_s(genre[index1], LENGTH, m[i].name); // genre 배열로 제목 복사
				index1++;
			}
		}
		for (;index1 < SIZE;index1++) // 이전 음악 재생에 의해 생성된 genre 배열 초기화
			strcpy_s(genre[index1], LENGTH, "?"); // 알파벳, NULL을 제외한 문자

		for (int i = 0;i < SIZE;i++)
		{
			if (i == n) // 선택 받은 음악은 제외
				continue;
			int x = strcmp(m[i].mood, m[n].mood); // 선택 받은 음악과 분위기가 같으면
			if (x == 0)
			{
				strcpy_s(mood[index2], LENGTH, m[i].name); // name 배열로 제목 복사
				index2++;
			}
		}
		for (;index2 < SIZE;index2++) // 이전 음악 재생에 의해 생성된 mood 배열 초기화
			strcpy_s(mood[index2], LENGTH, "?"); // 알파벳, NULL을 제외한 문자

//선택 받은 음악과 비슷한 장르, 분위기의 곡 리스트에 추가하는 알고리즘
		int x, y;
		printf("\n1 - 비슷한 장르\n");
		printf("2 - 비슷한 분위기\n");
		scanf_s("%d", &x);

		printf("\nplaylist\n"); // playlist 출력
		printf("%s\n", m[n].name);

		if (x == 1) // 비슷한 장르의 곡 추가
		{
			printf("추가\n");
			for (int i = 0;i < SIZE;i++)
			{
				if (((genre[i][0] >= 'A') && (genre[i][0] <= 'Z')) || ((genre[i][0] >= 'a') && (genre[i][0] <= 'z'))) // 쓰레기값 출력되지 않게 하기 위해
					printf("%s\n", genre[i]); // 제목이 복사된 배열(알파벳으로 시작하는 배열)만 출력
				else // 쓰레기값 들어있는 배열 만나면 for문 빠져나옴
					break;
			}

			printf("\n비슷한 분위기의 음악목록을 선택하시겠습니까?\n");
			printf("예-1\n");
			printf("아니오-0\n");
			scanf_s("%d", &y);

			if (y == 1) // 비슷한 분위기의 곡 추가
			{
				printf("\nplaylist\n"); // playlist 출력
				printf("%s\n", m[n].name); // 처음 선택한 곡
				for (int i = 0;i < SIZE;i++) // 추가된 비슷한 장르의 곡
				{
					if (((genre[i][0] >= 'A') && (genre[i][0] <= 'Z')) || ((genre[i][0] >= 'a') && (genre[i][0] <= 'z')))
						printf("%s\n", genre[i]);
					else
						break;
				}

				printf("추가\n");
				for (int i = 0;i < SIZE;i++)
				{
					for (int n = 0;n < SIZE;n++)
						if (strcmp(mood[i], genre[n]) == 0) // 비슷한 분위기의 곡이 앞서 추가된 비슷한 장르의 곡과 중복되는 것을 막기 위해
							mood[i][0] = NULL; // 추가될 비슷한 분위기의 곡들 중 추가된 비슷한 장르의 곡과 같은 것이 있다면, 첫번째 배열 NULL로 초기화

					if (((mood[i][0] >= 'A') && (mood[i][0] <= 'Z')) || ((mood[i][0] >= 'a') && (mood[i][0] <= 'z')))
						printf("%s\n", mood[i]);
					else if (mood[i][0] == NULL)
						continue;
					else // 첫번재 배열에 알파벳, NULL문자가 아닌 다른 문자가 있다면 for문 빠져나옴
						break;
				}
			}
		}

		else // 비슷한 분위기의 곡 추가
		{
			printf("추가\n");
			for (int i = 0;i < SIZE;i++)
			{
				if (((mood[i][0] >= 'A') && (mood[i][0] <= 'Z')) || ((mood[i][0] >= 'a') && (mood[i][0] <= 'z')))
					printf("%s\n", mood[i]);
				else
					break;
			}
			printf("\n비슷한 장르의 음악목록을 선택하시겠습니까?\n");
			printf("예-1\n");
			printf("아니오-0\n");
			scanf_s("%d", &y);
			
			if (y == 1) // 비슷한 장르의 곡 추가
			{
				printf("\nplaylist\n");
				printf("%s\n", m[n].name);
				for (int i = 0;i < SIZE;i++)
				{
					if (((mood[i][0] >= 'A') && (mood[i][0] <= 'Z')) || ((mood[i][0] >= 'a') && (mood[i][0] <= 'z')))
						printf("%s\n", mood[i]);
					else
						break;
				}

				printf("추가\n");
				for (int i = 0;i < SIZE;i++)
				{
					for (int n = 0;n < SIZE;n++)
						if (strcmp(genre[i], mood[n]) == 0)
							genre[i][0] = NULL;

					if (((genre[i][0] >= 'A') && (genre[i][0] <= 'Z')) || ((genre[i][0] >= 'a') && (genre[i][0] <= 'z')))
						printf("%s\n", genre[i]);
					else if (genre[i][0] == NULL)
						continue;
					else
						break;
				}
			}
		}

		int r;
		printf("\n0 - 음악 재생 중단\n");
		printf("1 - 음악 재생 계속\n");
		scanf_s("%d", &r);
		if (r == 0)
			break;
	}
	return 0;
}
