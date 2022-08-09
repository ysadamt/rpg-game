#include "cMain.h"
#include "Creature.h"
#include "Player.h"
#include "Monster.h"
#include "Random.h"
#include "choiceDialog.h"
#include "nameDialog.h"

#include <iostream>
#include <string>
#include <string_view>
#include <random>
#include <limits>
#include <chrono>
#include <thread>

// event table for "Play" button
wxBEGIN_EVENT_TABLE(cMain, wxFrame)
    EVT_BUTTON(10001, startGame)
wxEND_EVENT_TABLE()

void cMain::attackMonster(Player& player, Monster& monster)
{
    monster.reduceHealth(player.getDamage());   // reduce monster's health by player's current damage
    m_gameOutput->AppendText("You hit the " + monster.getName() + " for " + std::to_string(player.getDamage()) + " damage.\n");
}

void cMain::attackPlayer(Player& player, Monster& monster)
{
    player.reduceHealth(monster.getDamage());   // reduce player's health by monster's damage
    
    /* make text red */
    m_gameOutput->SetDefaultStyle(wxTextAttr(*wxRED));
    m_gameOutput->AppendText("The " + monster.getName() + " hit you for " + std::to_string(monster.getDamage()) + " damage.\n");
    m_gameOutput->SetDefaultStyle(wxTextAttr(wxNullColour));
}

void cMain::fightMonster(Player& player, Monster& monster)
{
    // loop breaks either when monster is dead or player is dead
    while (monster.getHealth() > 0 && player.getHealth() > 0)
    {
        choiceDialog* dlg{ new choiceDialog() };    // new pop up dialog
        dlg->ShowModal();                           // can't interact with main window when dialog appears
        char choice{ dlg->getChoice() };            // get choice char from buttons: 'f' for Fight, 'r' for Run
        delete dlg;

        if (choice == 'f')
        {
            attackMonster(player, monster);
            if (monster.getHealth() <= 0)
            {
                m_gameOutput->AppendText("You killed the " + monster.getName() + ".\n");

                player.levelUp();   // player levels up by 1

                /* make text bold */
                m_gameOutput->SetDefaultStyle(*m_bold);
                m_gameOutput->AppendText("\nLEVEL UP! You are now level " + std::to_string(player.getLevel()) + ".\n");
                m_gameOutput->SetDefaultStyle(wxTextAttr(wxNullColour));

                if (!(player.getLevel() % 5))
                {
                    player.replenishHealth();   // replenish player health back to 10 every 5 levels

                    /* make text green */
                    m_gameOutput->SetDefaultStyle(wxTextAttr(wxColour(22, 120, 2)));
                    m_gameOutput->AppendText("Health replenished!\n");
                    m_gameOutput->SetDefaultStyle(wxTextAttr(wxNullColour));

                }

                player.addGold(monster.getGold());  // player gets the gold the monster is carrying

                /* make text gold */
                m_gameOutput->SetDefaultStyle(wxTextAttr(wxColour(196, 155, 8)));
                m_gameOutput->AppendText("You found " + std::to_string(monster.getGold()) + " gold.\n");
                m_gameOutput->SetDefaultStyle(wxTextAttr(wxNullColour));

                /* update stat box after player kills a monster */
                m_statBox->Clear();
                printStats(player);
            }
            else
            {
                attackPlayer(player, monster);

                /* update stat box after monster attacks player */
                m_statBox->Clear();
                printStats(player);
            }
        }

        else if (choice == 'r')
        {
            int chance{ Random::getRandomNumber(0, 1) };    // 50% chance of running

            if (chance == 0)
            {
                m_gameOutput->AppendText("You failed to flee.\n");
                attackPlayer(player, monster);

                /* update stat box after player fails to flee and monster attacks as a result */
                m_statBox->Clear();
                printStats(player);
            }
            else
            {
                m_gameOutput->AppendText("You successfully fled.\n");
                break;  // break loop after fleeing, move on to next monster
            }
        }
    }
}

void cMain::printStats(Player& player) const
{
    m_statBox->AppendText("Name:\t" + player.getName() + '\n');
    m_statBox->AppendText("Level: \t" + std::to_string(player.getLevel()) + '\n');

    if (player.getHealth() > 0)
    {
        m_statBox->AppendText("Health:\t" + std::to_string(player.getHealth()) + '\n');
    }
    else
    {
        m_statBox->AppendText("Health:\t" + std::to_string(0) + '\n');  // prevent printing negative health
    }

    m_statBox->AppendText("Damage:\t" + std::to_string(player.getDamage()) + '\n');
    m_statBox->AppendText("Gold:\t" + std::to_string(player.getGold()) + '\n');
}

void cMain::startGame(wxCommandEvent& evt)
{
    m_gameOutput->Clear();  // clear game output box whenever user starts a new game
    m_statBox->Clear();     // clear stat box whenever user starts a new game

    nameDialog* nameDlg{ new nameDialog() };    // dialog pops up, prompts user for name

    if (nameDlg->ShowModal() == 1)  // if user presses OK
    {
        Player p{ nameDlg->getName() }; // create Player
        delete nameDlg;

        /* make welcome text bold */
        m_gameOutput->SetDefaultStyle(*m_bold);
        m_gameOutput->AppendText("Welcome, " + p.getName() + ".\n");
        m_gameOutput->SetDefaultStyle(wxTextAttr(wxNullColour));

        // main game loop
        while (!p.hasWon() && p.getHealth() > 0)
        {
            /* print stat box when game starts */
            m_statBox->Clear();
            printStats(p);

            Monster m{ Monster::getRandomMonster() };   // create Monster

            std::this_thread::sleep_for(std::chrono::milliseconds(200));    // short pause in between fighting each monster

            m_gameOutput->AppendText("\nYou have encountered a(n) " + m.getName() + " (" + m.getSymbol() + ").\n");
            fightMonster(p, m);
        }

        // message if player won
        if (p.hasWon())
        {
            /* make winning message bold */
            m_gameOutput->SetDefaultStyle(*m_bold);
            m_gameOutput->AppendText("\nCongratulations, you won! You reached level " + std::to_string(p.getLevel()) + " with " + std::to_string(p.getGold()) + " gold.\n");
            m_gameOutput->SetDefaultStyle(wxTextAttr(wxNullColour));

        }
        // message if player lost
        else
        {
            /* make losing message bold */
            m_gameOutput->SetDefaultStyle(*m_bold);
            m_gameOutput->AppendText("\nYou died at level " + std::to_string(p.getLevel()) + " and with " + std::to_string(p.getGold()) + " gold.\n");
            m_gameOutput->AppendText("Too bad you can't take it with you!\n");
            m_gameOutput->SetDefaultStyle(wxTextAttr(wxNullColour));
        }
    }
}