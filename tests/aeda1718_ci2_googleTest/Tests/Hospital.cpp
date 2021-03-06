/*
 * Hospital.cpp
 */

#include "Hospital.h"
//
#include <algorithm>


Hospital::Hospital(unsigned trayC):trayCapacity(trayC)
{ }

void Hospital::addDoctor(const Doctor &d1) {
	doctors.push_back(d1);
}

list<Doctor> Hospital::getDoctors() const {
	return doctors;
}

void Hospital::addTrays(stack<Patient> tray1) {
	letterTray.push_back(tray1);
}

list<stack<Patient> > Hospital::getTrays() const {
	return letterTray;
}



unsigned Hospital::numPatients(string medicalSpecialty) const
{
    unsigned count = 0;
	for (auto it = doctors.begin(); it != doctors.end(); it++)
        if (it->getMedicalSpecialty() == medicalSpecialty)
            count += it->getPatients().size();
    return count;
}

bool foo (const Doctor &d1, const Doctor &d2) {
    if (d1.getPatients().size() < d2.getPatients().size())
        return true;
    if (d1.getPatients().size() > d2.getPatients().size())
        return false;
    if (d1.getMedicalSpecialty() < d2.getMedicalSpecialty())
        return true;
    if (d1.getMedicalSpecialty() > d2.getMedicalSpecialty())
        return false;
    return d1.getCode() < d2.getCode();
}

void Hospital::sortDoctors() {
    doctors.sort(foo);
}



bool Hospital::addDoctor(unsigned codM1, string medicalSpecialty1) {

	int count = 0;
	for (auto & doctor : doctors)
	    if (doctor.getMedicalSpecialty() == medicalSpecialty1)
	        count++;
	if (count < 3) {
        doctors.emplace_back(codM1, medicalSpecialty1);
        return true;
    }
	else
	    return false;
}



queue<Patient> Hospital::removeDoctor(unsigned codM1) {

    for (auto it = doctors.begin(); it != doctors.end(); it++)
        if (it->getCode() == codM1) {
            queue<Patient> p = it->getPatients();
            doctors.erase(it);
            return p;
        }
    throw DoctorInexistent();
}


bool Hospital::putInLessBusyDoctor(unsigned cod1, string medicalSpecialty1) {

    bool flag = false;
    for (auto &doc : doctors)
        if (doc.getMedicalSpecialty() == medicalSpecialty1)
            flag = true;

    if (!flag) return false;

    Doctor *menosOcupado = &doctors.front();

    for (auto &doc : doctors)
        if (doc.getPatients().size() < menosOcupado->getPatients().size() && doc.getMedicalSpecialty() == medicalSpecialty1)
            menosOcupado = &doc;

    menosOcupado->addPatient(Patient(cod1,medicalSpecialty1));
    return true;
}



void Hospital::processPatient(unsigned codM1) {

    bool isDoc = false;
    Patient patient(1,"");
    for (auto& doc : doctors)
        if (doc.getCode() == codM1) {
            try {
                patient = doc.removeNextPatient();
                isDoc = true;
            }
            catch (Doctor::PatientInexistent &e) { }
        }

    if (!isDoc) return;

    for (auto& tray : letterTray)
        if (tray.size() != trayCapacity) {
            tray.push(patient);
            return;
        }

    stack<Patient> p1;
    p1.push(patient);
    addTrays(p1);
}


unsigned Hospital::removePatients(unsigned codP1) {

    int count = 0;
    for (auto it = letterTray.begin(); it != letterTray.end(); it++) {
        if (it->top().getCode() == codP1) {
            it->pop();
            count++;
        }
        if (it->empty())
            it = --letterTray.erase(it);
    }
    return count;
}



