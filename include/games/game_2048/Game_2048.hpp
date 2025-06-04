//
// Created by qingzhixing on 2025/6/4.
//
#pragma once

#ifndef GAME_2048_HPP
#define GAME_2048_HPP
#include <cstring>

#include <Coord.hpp>
#include <WString.h>
#include <vector>
#include <Arduino.h>
#include <random>

typedef enum Game2048Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
} Game2048Direction;

static Coord direction_to_coord(const Game2048Direction direction)
{
    switch (direction)
    {
    case UP:
        return {0, -1};
    case DOWN:
        return {0, 1};
    case LEFT:
        return {-1, 0};
    case RIGHT:
        return {1, 0};
    default:
        return {0, 0};
    }
}

static Game2048Direction directions[4] = {UP, DOWN, LEFT, RIGHT};

class Game_2048
{
public:
    int max_score = 0;
    int score = 0;
    uint16_t game_map[4][4] = {};
    bool in_game = false;

private:
    /**
     * 处理单行/单列的移动和合并逻辑
     * @param line 要处理的行/列（一维数组）
     * @return 本次处理新增的分数
     */
    static int process_line(uint16_t line[4])
    {
        int score_add = 0;
        // 第一步：紧凑（移除空格）
        uint16_t write_index = 0;
        for (int i = 0; i < 4; i++)
        {
            if (line[i] != 0)
            {
                if (i != write_index)
                {
                    line[write_index] = line[i];
                    line[i] = 0;
                }
                write_index++;
            }
        }

        // 第二步：合并相同数字（幂次加1）
        for (int i = 0; i < 3; i++)
        {
            if (line[i] != 0 && line[i] == line[i + 1])
            {
                line[i]++; // 幂次加1（相当于值乘以2）
                line[i + 1] = 0;
                // 分数增加 = 2^(新幂次) = 2^(line[i])
                score_add += (1 << line[i]);
            }
        }

        // 第三步：再次紧凑（合并后可能有新空格）
        write_index = 0;
        for (int i = 0; i < 4; i++)
        {
            if (line[i] != 0)
            {
                if (i != write_index)
                {
                    line[write_index] = line[i];
                    line[i] = 0;
                }
                write_index++;
            }
        }
        return score_add;
    }

public:
    void generate_new_number()
    {
        // 初始化空位置列表
        std::vector<Coord> empty_array;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (game_map[i][j] == 0)
                {
                    empty_array.emplace_back(i, j);
                    Serial.println("empty_array.emplace_back(" + String(i) + "," + String(j) + ")");
                }
            }
        }
        if (empty_array.empty())
            return;

        // 随机抽取
        const Coord& coord = empty_array[esp_random() % empty_array.size()];

        // 生成数字,50%概率生成1(2^1),50%概率生成2(2^2)
        game_map[coord.x][coord.y] = esp_random() % 2 + 1;

        Serial.println("game_map[" + String(coord.x) + "][" + String(coord.y) +
                       "] = " + String(game_map[coord.x][coord.y]));
    }

    void start_new_game()
    {
        // 清空数据
        memset(game_map, 0, sizeof(game_map));
        score = 0;

        // 设置状态
        in_game = true;

        generate_new_number();
    }

    bool is_game_over() const
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (game_map[i][j] == 0)
                    return false;
                for (auto const& direction : directions)
                {
                    const Coord judging_coord = Coord(i, j) + direction_to_coord(direction);
                    if (judging_coord.x < 0 || judging_coord.x >= 4 || judging_coord.y < 0 || judging_coord.y >= 4)
                        continue;
                    if (game_map[i][j] == game_map[judging_coord.x][judging_coord.y])
                        return false;
                }
            }
        }
        return true;
    }

    void do_game_input(const Game2048Direction direction)
    {
        // if (is_game_over())
        //     return;

        // 保存移动前的地图状态，用于检测是否有变化
        int old_map[4][4];
        std::memcpy(old_map, game_map, sizeof(game_map));
        int score_add = 0; // 本次移动新增的分数

        // 根据方向选择处理方式
        switch (direction)
        {
        case UP:
            // 更新每一列的状态
            for (int col = 0; col < 4; col++)
            {
                uint16_t line[4] = {game_map[0][col], game_map[1][col], game_map[2][col], game_map[3][col]};
                score_add += process_line(line);
                for (int i = 0; i < 4; i++)
                {
                    game_map[i][col] = line[i];
                }
            }
            break;

        case DOWN:
            // 更新每一列的状态
            for (int col = 0; col < 4; col++)
            {
                // 反转列，处理后再反转回来
                uint16_t line[4] = {game_map[3][col], game_map[2][col], game_map[1][col], game_map[0][col]};
                score_add += process_line(line);
                for (int i = 0; i < 4; i++)
                {
                    game_map[i][col] = line[3 - i];
                }
            }
            break;

        case LEFT:
            // 更新每一行的状态
            for (auto& row : game_map)
            {
                score_add += process_line(row);
            }
            break;

        case RIGHT:
            // 更新每一行的状态
            for (auto& row : game_map)
            {
                // 反转行，处理后再反转回来
                uint16_t line[4] = {row[3], row[2], row[1], row[0]};
                score_add += process_line(line);
                for (int i = 0; i < 4; i++)
                {
                    row[i] = line[3 - i];
                }
            }
            break;
        }

        // 更新分数
        score += score_add;

        // 更新历史最高分
        if (score > max_score)
        {
            max_score = score;
        }

        // 如果地图发生变化，生成新数字
        if (std::memcmp(old_map, game_map, sizeof(game_map)) != 0)
        {
            generate_new_number();
        }
    }
};

#endif // GAME_2048_HPP
