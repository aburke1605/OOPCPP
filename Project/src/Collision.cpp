#include "../include/Collision.h"
#include "../include/Colours.h"

#include <cfloat>

const std::map<std::string, sf::Color> collision::colours
{
	{"ELECTRON", CustomColour::Magenta}, {"ANTIELECTRON", CustomColour::Magenta},
	{"ELECTRON-NEUTRINO", CustomColour::Magenta}, {"ANTIELECTRON-NEUTRINO", CustomColour::Magenta},
	{"MUON", CustomColour::Blue}, {"ANTIMUON", CustomColour::Blue},
	{"MUON-NEUTRINO", CustomColour::Blue}, {"ANTIMUON-NEUTRINO", CustomColour::Blue},
	{"TAU", CustomColour::Green}, {"ANTITAU", CustomColour::Green},
	{"TAU-NEUTRINO", CustomColour::Green}, {"ANTITAU-NEUTRINO", CustomColour::Green},
	{"UP", CustomColour::Red}, {"ANTIUP", CustomColour::Red},
	{"DOWN", CustomColour::Red}, {"ANTIDOWN", CustomColour::Red},
	{"CHARM", CustomColour::Red}, {"ANTICHARM", CustomColour::Red},
	{"STRANGE", CustomColour::Red}, {"ANTISTRANGE", CustomColour::Red},
	{"TOP", CustomColour::Red}, {"ANTITOP", CustomColour::Red},
	{"BOTTOM", CustomColour::Red}, {"ANTIBOTTOM", CustomColour::Red},
	{"PHOTON", CustomColour::Yellow},
	{"Z BOSON", CustomColour::Black},
	{"W BOSON", CustomColour::Black}, {"ANTIW BOSON", CustomColour::Black}
};

const std::vector<std::shared_ptr<detector>> collision::detector_segments
{
	std::make_shared<tracker>(0, 20),
	std::make_shared<e_calorimeter>(20, 75),
	std::make_shared<h_calorimeter>(75, 150),
	std::make_shared<muon_chamber>(150, 250)
};

collision::collision(Session& session)
{
	/*
	The collision constructor simulates a collision between protons at the LHC
	by using the 'random_number()' function to select 2 partons to collide,
	and to decide how they interact/what particles emerge from the collision.
	args:    N/A (default constructor only)
	returns: Generates an instance of the collision class which contains a vector
	         of the emerging particles from the collision.
	*/

	std::map<std::string, std::unique_ptr<particle>> colliding_particles;
	bool positive_z_direction{ false };
	int up_counter{}, down_counter{}, gluon_counter{};
	while (colliding_particles.size() < 2) {
		if (colliding_particles.size() == 1) {
			positive_z_direction = true;
		}
		
		double parton_selection{ random_number<double>(0.0, 1.0) };
		double bjorken_x{ random_number<double>(0.015, 0.075) }; // E [0.015, 0.075] 6.5 TeV
		if (parton_selection < 1.0 / 3) {
			up_counter++;
			colliding_particles["u" + std::to_string(up_counter)] = std::make_unique<up>((13e3 / 2) * bjorken_x, pi * positive_z_direction, 0.0);
		}
		else if (parton_selection < 2.0 / 3) {
			down_counter++;
			colliding_particles["d" + std::to_string(down_counter)] = std::make_unique<down>((13e3 / 2) * bjorken_x, pi * positive_z_direction, 0.0);
		}
		else {
			gluon_counter++;
			colliding_particles["g" + std::to_string(gluon_counter)] = std::make_unique<gluon>((13e3 / 2) * bjorken_x, pi * positive_z_direction, 0.0);
		}
	}

	double random{ random_number<double>(0.0, 1.0) };
	if (colliding_particles.find("g1") != colliding_particles.end()) { // gg or gq
		if (colliding_particles.find("g2") != colliding_particles.end()) { // gg
			if (random < 1.0 / 3) { // fuse the gluons
				double x_momentum{ colliding_particles.find("g1")->second->get_momentum_vector()[0] + colliding_particles.find("g2")->second->get_momentum_vector()[0] };
				double y_momentum{ colliding_particles.find("g1")->second->get_momentum_vector()[1] + colliding_particles.find("g2")->second->get_momentum_vector()[1] };
				double z_momentum{ colliding_particles.find("g1")->second->get_momentum_vector()[2] + colliding_particles.find("g2")->second->get_momentum_vector()[2] };
				std::unique_ptr<particle> fused_gluon{ std::make_unique<gluon>() };
				std::vector<double> momentum{ x_momentum, y_momentum, z_momentum };
				fused_gluon->set_momentum(momentum);
				fused_gluon->set_decay_modes();
				particles.push_back(std::make_pair(std::move(fused_gluon->get_decay_particles()[0]), centre()));
				particles.push_back(std::make_pair(std::move(fused_gluon->get_decay_particles()[1]), centre()));
			}
			else {
				// decay one of the gluons and push one of the daughters to particles
				colliding_particles.find("g2")->second->set_decay_modes();
				particles.push_back(std::make_pair(std::move(colliding_particles.find("g2")->second->get_decay_particles()[1]), centre()));
				if (colliding_particles.find("g2")->second->get_decay_particles()[0]->get_type() == "UP") {
					colliding_particles["u1"] = std::move(colliding_particles.find("g2")->second->get_decay_particles()[0]);
				}
				else {
					colliding_particles["d1"] = std::move(colliding_particles.find("g2")->second->get_decay_particles()[0]);
				}
				colliding_particles.erase(colliding_particles.find("g2"));
				if (random < 2.0 / 3) {
					// decay the other gluon too
					colliding_particles.find("g1")->second->set_decay_modes();
					particles.push_back(std::make_pair(std::move(colliding_particles.find("g1")->second->get_decay_particles()[0]), centre()));

					double x_momentum{ colliding_particles.find("g1")->second->get_decay_particles()[1]->get_momentum_vector()[0] };
					double y_momentum{ colliding_particles.find("g1")->second->get_decay_particles()[1]->get_momentum_vector()[1] };
					double z_momentum{ colliding_particles.find("g1")->second->get_decay_particles()[1]->get_momentum_vector()[2] };
					std::vector<double> momentum;
					std::unique_ptr<particle> boson;
					std::string type{ colliding_particles.find("g1")->second->get_decay_particles()[1]->get_type() };
					type = type.substr(4, type.length() - 4); // "UP" or "DOWN"
					for (auto it{ colliding_particles.begin() }; it != colliding_particles.end(); it++) {
						if (it->first != "g1") {
							x_momentum += it->second->get_momentum_vector()[0];
							y_momentum += it->second->get_momentum_vector()[1];
							z_momentum += it->second->get_momentum_vector()[2];
							if (type == it->first) { // make a z_boson or a photon
								if (random < 1.0 / 2) {
									boson = std::make_unique<z_boson>();
								}
								else {
									boson = std::make_unique<photon>();
								}
							}
							else { // make a w- or w+_boson
								double charge{ colliding_particles.find("g1")->second->get_decay_particles()[1]->get_charge() + it->second->get_charge() };
								if (charge < 0.0) {
									boson = std::make_unique<w_boson>();
								}else{
									boson = std::make_unique<w_boson>(true);
								}
							}
							momentum.push_back(x_momentum); momentum.push_back(y_momentum); momentum.push_back(z_momentum);
							boson->set_momentum(momentum);
							particles.push_back(std::make_pair(std::move(boson), centre()));
						}
					}
					colliding_particles.erase(colliding_particles.find("g1"));
				}
			}
		}
	}
	if (colliding_particles.find("g1") != colliding_particles.end() && colliding_particles.find("g2") == colliding_particles.end()) { // gq
		random = random_number<double>(0.0, 1.0);
		if (random < 0.8) { // 80 % of the time the gluon decays to up-antiup or down-antidown
			colliding_particles.find("g1")->second->set_decay_modes();
			particles.push_back(std::make_pair(std::move(colliding_particles.find("g1")->second->get_decay_particles()[0]), centre()));
			double x_momentum{ colliding_particles.find("g1")->second->get_decay_particles()[1]->get_momentum_vector()[0] };
			double y_momentum{ colliding_particles.find("g1")->second->get_decay_particles()[1]->get_momentum_vector()[1] };
			double z_momentum{ colliding_particles.find("g1")->second->get_decay_particles()[1]->get_momentum_vector()[2] };
			std::unique_ptr<particle> boson;
			std::string type{ colliding_particles.find("g1")->second->get_decay_particles()[1]->get_type() };
			type = type.substr(4, type.length() - 4);
			for (auto it{ colliding_particles.begin() }; it != colliding_particles.end(); it++) {
				if (it->first != "g1") {
					x_momentum += it->second->get_momentum_vector()[0];
					y_momentum += it->second->get_momentum_vector()[1];
					z_momentum += it->second->get_momentum_vector()[2];
					if (type == it->second->get_type()) {
						// z_boson or photon
						if (random < 1.0 / 4) {
							boson = std::make_unique<z_boson>();
						}else{
							boson = std::make_unique<photon>();
						}
					}
					else {
						// w_boson
						if (it->second->get_charge() + colliding_particles.find("g1")->second->get_decay_particles()[1]->get_charge() < 0) {
							boson = std::make_unique<w_boson>();
						}
						else {
							boson = std::make_unique<w_boson>(true);
						}
					}
				}
			}
			std::vector<double> momentum{ x_momentum, y_momentum, z_momentum };
			boson->set_momentum(momentum);
			particles.push_back(std::make_pair(std::move(boson), centre()));
		}
		else {
			double momentum_x{}, momentum_y{}, momentum_z{};
			for (auto it{ colliding_particles.begin() }; it != colliding_particles.end(); it++) {
				momentum_x += (it->second->get_momentum_vector())[0];
				momentum_y += (it->second->get_momentum_vector())[1];
				momentum_z += (it->second->get_momentum_vector())[2];
			}
			std::vector<double> momentum{ momentum_x, momentum_y, momentum_z };

			if (colliding_particles.find("d1") == colliding_particles.end()) { // q is an up quark
				particles.push_back(std::make_pair(std::make_unique<up>(), centre()));
			}
			else { // q is a down quark
				particles.push_back(std::make_pair(std::make_unique<down>(), centre()));
			}
			particles[particles.size() - 1].first->set_momentum(momentum);
		}
	}
	else if(colliding_particles.find("u2") != colliding_particles.end()	|| colliding_particles.find("d2") != colliding_particles.end()	|| (colliding_particles.find("u1") != colliding_particles.end() && colliding_particles.find("d1") != colliding_particles.end())) { // qq
		// VBF
		if (colliding_particles.find("d1") != colliding_particles.end() && colliding_particles.find("d2") == colliding_particles.end()) {
			auto initial_down{ std::move(colliding_particles.find("d1")->second) };
			initial_down->set_decay_modes(); // goes to up + w_boson

			auto initial_up{ std::move(colliding_particles.find("u1")->second) };
			std::vector<std::vector<std::unique_ptr<particle>>> temporary;
			std::vector<std::unique_ptr<particle>> temporary_channel;
			temporary_channel.push_back(std::make_unique<up>()); temporary_channel.push_back(std::make_unique<z_boson>());
			temporary.push_back(std::move(temporary_channel));
			initial_up->set_decay_particles(temporary);
			initial_up->decay(*initial_up); // goes to up + z_boson

			std::unique_ptr<particle> final_w_boson{ std::make_unique<w_boson>() };
			double x_momentum{ initial_down->get_decay_particles()[1]->get_momentum_vector()[0] + initial_up->get_decay_particles()[1]->get_momentum_vector()[0] };
			double y_momentum{ initial_down->get_decay_particles()[1]->get_momentum_vector()[1] + initial_up->get_decay_particles()[1]->get_momentum_vector()[1] };
			double z_momentum{ initial_down->get_decay_particles()[1]->get_momentum_vector()[2] + initial_up->get_decay_particles()[1]->get_momentum_vector()[2] };
			std::vector<double> momentum{ x_momentum, y_momentum, z_momentum };
			final_w_boson->set_momentum(momentum);
			particles.push_back(std::make_pair(std::move(final_w_boson), centre()));
			particles.push_back(std::make_pair(std::move(initial_down->get_decay_particles()[0]), centre()));
			particles.push_back(std::make_pair(std::move(initial_up->get_decay_particles()[0]), centre()));
		}
		else {
			// produce two Z bosons, one from each quark, that merge to one Z boson
			auto partons{ colliding_particles.begin() };
			std::unique_ptr<particle> quark_1{ std::move(partons->second) };
			partons++;
			std::unique_ptr<particle> quark_2{ std::move(partons->second) };

			std::vector<std::unique_ptr<particle>> quark_1_channel;
			std::vector<std::unique_ptr<particle>> quark_2_channel;
			if (quark_1->get_type() == "UP") {
				quark_1_channel.push_back(std::make_unique<up>());
				quark_2_channel.push_back(std::make_unique<up>());
			}
			else {
				quark_1_channel.push_back(std::make_unique<down>());
				quark_2_channel.push_back(std::make_unique<down>());
			}
			quark_1_channel.push_back(std::make_unique<z_boson>());
			quark_2_channel.push_back(std::make_unique<z_boson>());

			std::vector<std::vector<std::unique_ptr<particle>>> decay_particles_1;
			decay_particles_1.push_back(std::move(quark_1_channel));
			quark_1->set_decay_particles(decay_particles_1);
			quark_1->decay(*quark_1);
			std::vector<std::vector<std::unique_ptr<particle>>> decay_particles_2;
			decay_particles_2.push_back(std::move(quark_2_channel));
			quark_2->set_decay_particles(decay_particles_2);
			quark_2->decay(*quark_2);

			std::unique_ptr<particle> final_z_boson{ std::make_unique<z_boson>() };
			double x_momentum{ quark_1->get_decay_particles()[1]->get_momentum_vector()[0]
				+ quark_2->get_decay_particles()[1]->get_momentum_vector()[0] };
			double y_momentum{ quark_1->get_decay_particles()[1]->get_momentum_vector()[1]
				+ quark_2->get_decay_particles()[1]->get_momentum_vector()[1] };
			double z_momentum{ quark_1->get_decay_particles()[1]->get_momentum_vector()[2]
				+ quark_2->get_decay_particles()[1]->get_momentum_vector()[2] };
			std::vector<double> momentum{ x_momentum, y_momentum, z_momentum };
			final_z_boson->set_momentum(momentum);

			particles.push_back(std::make_pair(std::move(quark_1->get_decay_particles()[0]), centre()));
			particles.push_back(std::make_pair(std::move(quark_2->get_decay_particles()[0]), centre()));
			particles.push_back(std::make_pair(std::move(final_z_boson), centre()));
		}
	}

	this->draw_event(session);
}

collision::collision(Session& session, std::unique_ptr<particle>& p)
{
	particles.push_back(std::make_pair(std::move(p), centre()));
	this->draw_event(session);
}

collision::~collision()
{
	//std::cout << "Collision destructor called" << std::endl;
}

const std::pair<double, double>& collision::centre()
{
	return detector_segments[0]->centre();
}

void collision::draw_event(Session& session) {
	/*
	A function  to display the trajectories of all particles generated
	in any 'collision' instance. The function invoked decays and draws
	these particles too.
	args:    N/A
	returns: A drawing to the console window for each particle
	         in the 'particles' container
	*/

	// first draw detector
	if (!session.detector) {
		for (auto it{ detector_segments.begin() }; it != detector_segments.end(); it++)
			(*it)->draw_detector(session.window);
		session.detector = true;
		// session.window.display();
	}

	for (int j{}; j < (int)particles.size(); j++){
		auto it{ &particles.at(j) };
		sf::Color colour{ colours.find(it->first->get_type())->second };

		double radius_of_curvature{}; // has to be calculated before energy is subtracted
		if (it->first->get_charge() != 0.0) {
			radius_of_curvature = (it->first->get_energy()) / (std::abs(it->first->get_charge()) * 2.0); // 2 Tesla
			radius_of_curvature *= sqrt(1 - pow(it->first->get_mass() / it->first->get_energy(), 2));
			radius_of_curvature *= 7; // for visual
		}
		if (radius_of_curvature <= detector_segments[detector_segments.size() - 1]->get_outer_radius()) {
			radius_of_curvature = 0.75 * detector_segments[detector_segments.size() - 1]->get_outer_radius();
		}
		double centre_phi{ it->first->get_phi() + pi / 2 };
		if (it->first->get_charge() < 0) { // curves the opposite way
			centre_phi -= pi;
		}
		double centre_of_curvature_x{ it->second.first + radius_of_curvature * cos(centre_phi) };
		double centre_of_curvature_y{ it->second.second + radius_of_curvature * sin(centre_phi) };

		int iteration_number{};
		double r{};
		double distance_travelled{};
		double X{ it->second.first },
			Y{ it->second.second };
		double original_X{ X }, original_Y{ Y };
		bool propagating{ true };
		while (propagating) {
			auto segment{ std::find_if(detector_segments.begin(), detector_segments.end(), [X, Y](auto iterator)->bool
				{
					return sqrt(pow(X - iterator->centre().first, 2) + pow(Y - iterator->centre().second, 2)) < iterator->get_outer_radius();
				}) };
			if (segment != detector_segments.end()) {
				// first: propagate a step
				if (it->first->get_charge() == 0.0) {
					X = (r * cos(it->first->get_phi()) + it->second.first);
					Y = (r * sin(it->first->get_phi()) + it->second.second);
				}
				else {
					if (it->first->get_charge() > 0.0) {
						X = (radius_of_curvature * cos(it->first->get_phi() + 3 * pi / 2) + centre_of_curvature_x);
						Y = (radius_of_curvature * sin(it->first->get_phi() + 3 * pi / 2) + centre_of_curvature_y);
						it->first->set_phi(it->first->get_phi() + 1 / radius_of_curvature);
					}
					else {
						X = (radius_of_curvature * cos(it->first->get_phi() - 3 * pi / 2) + centre_of_curvature_x);
						Y = (radius_of_curvature * sin(it->first->get_phi() - 3 * pi / 2) + centre_of_curvature_y);
						it->first->set_phi(it->first->get_phi() - 1 / radius_of_curvature);
					}
				}
				sf::RectangleShape pixel(sf::Vector2f(1.0, 1.0));
				pixel.setFillColor(colour);
				pixel.setPosition(X, Y);
				session.window.draw(pixel);
				it->second.first = X;
				it->second.second = Y;

				// second: check for interaction
				double interaction_distance{ DBL_MAX };
				std::for_each((*segment)->get_interactions().begin(), (*segment)->get_interactions().end(), [&distance_travelled, &interaction_distance, &it](auto iterator)
					{
						if (iterator.first == it->first->get_type()) {
							interaction_distance = it->first->get_energy() * iterator.second;
							distance_travelled += 1;
						}
					}
				);
				if (distance_travelled >= interaction_distance) {
					it->first->set_decay_modes();
					std::vector<std::unique_ptr<particle>> daughters{ std::move(it->first->get_decay_particles()) };
					if (daughters.size() > 0) {
						for (auto et{ daughters.begin() }; et != daughters.end(); et++) {
							if (particles.size() < 100) {
								particles.insert(particles.end(), std::make_pair(std::move(*et), std::make_pair(X, Y)));
							}
						}
					}
					propagating = false;
				}
			}
			else {
				propagating = false;
			}
			r += 0.01;
			iteration_number++;
			// catch infinite loops
			if (iteration_number > 1000) {
				propagating = false;
			}
		}
		// session.window.display();
	}
}